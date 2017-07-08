#include <string.h>
#include <stdio.h>
#include "btrees.h"
#include "frag_curs.h"
#include "frag_fh.h"
#include "frag_svc.h"
#include "hierr.h"


static struct frag_fh *frag_curs_node_new( struct hiena_frag *f )
{
        struct frag_fh *ffh;

        ffh = frag_fh_new();
        ffh->frag = f;
        ffh->off  = 0;
        ffh->mfrag_fh = NULL;
}

static void frag_curs_node_cleanup( struct frag_fh *ffh )
{
        frag_fh_cleanup( ffh );
}



struct frag_curs *frag_curs_new( struct hiena_frag *f )
{
        struct frag_curs *fc;
        struct frag_fh *root;

        root = frag_curs_node_new(f);
        root->outer_fh = root;


        fc = malloc(sizeof(*fc));
        memset(fc, 0, sizeof(*fc));
        fc->root = root;
        fc->cur = root;

        return fc;
}

int frag_curs_cleanup( struct frag_curs *fc )
{
        if( fc == NULL )
                return -1;

        frag_svc_close( fc->root );

        free(fc);

        return 0;
}

int frag_curs_step_inward( struct frag_curs *fc )
{
        return -1;
}

int frag_curs_step_into( struct frag_curs *fc, struct hiena_frag *f, size_t new_off )
{
        if( fc == NULL )
        {
                HIERR("frag_curs_step_into: err: fc NULL");
                 return -1;
        }

        if( f == NULL )
        {
                HIERR("frag_curs_step_into: err: f NULL");
                 return -1;
        }

        struct frag_fh *cur;
        struct frag_fh *cursav;

        cur = fc->cur;
        cursav = cur;

        cur = frag_curs_node_new(f);
        cur->outer_fh = cursav;
        cur->off = new_off;

        cursav->inner_fh = cur;

        fc->cur = cur;

        return 0;
}

int frag_curs_step_outward( struct frag_curs *fc )
{
        if( fc == NULL )
        {
                HIERR("frag_curs_step_out: err: fc NULL");
                return -1;
        }

        struct frag_fh *cur;
        struct frag_fh *outer;
        size_t off;

        cur = fc->cur;

        if( cur == fc->root )
        {
                HIERR("frag_curs_step_out: err: cur is root, can't step out.");
                return -2;
        }

        outer = cur->outer_fh;

        if( cur == outer )
        {
                HIERR("frag_curs_step_out: err: cur is outer, can't step out.");
                return -3;
        }


        /* important:
           this tracks position */

        off = outer->off + cur->off;
        outer->off = off;

        fc->cur = outer;

        frag_curs_node_cleanup(cur);

        return 0;
}


struct hiena_frag *frag_curs_find_deepest_has_room( struct frag_curs *fcurs, size_t len )
{
        struct hiena_frag *f, *cf;
        size_t off, new_off;
        bnode_t n;

        f = fcurs->cur->frag;
        off = fcurs->cur->off;


        if( frag_has_room( f, off, len ))
                goto find_child;
        else
                goto find_parent;

find_child:

        cf = (struct hiena_frag *) bnode_value_at_key_or_nearest_lesser(f->children->root, (bkey_t)off, (void **)&new_off);

        if(frag_has_room( cf, off, len ))
        {
                
frag_curs_step_into( fcurs, cf, new_off );
                f = cf;
                off = new_off;
                goto find_child;
        }

        return f;

find_parent:

        switch(frag_curs_step_outward(fcurs))
       {
        case -1:
                HIERR("frag_curs_find_deepest_has_room: improbable: parent null");
                return NULL;
        case -2:
                HIERR("frag_curs_find_deepest_has_room: frag has no parent and no room");
                return NULL;
        case -3:
                HIERR("frag_curs_find_deepest_has_room: improbable: frag has no parent ");
                return NULL;
        default:
                break;
        }

        f = fcurs->cur->frag;

        if(!frag_has_room( f, off, len ))
               goto find_parent;

        return f;
}



struct hiena_frag *frag_curs_find_deepest( struct frag_curs *fc )
{
        return frag_curs_find_deepest_has_room( fc, 0 );
}



int frag_curs_seek( struct frag_curs *fc, size_t off, int whence)
{
        if( fc == NULL )
        {
                HIERR("frag_curs_seek err: fc NULL");
                return -1;
        }

        switch( whence )
        {
        case SEEK_SET:

                break;
        case SEEK_CUR:
                frag_curs_find_deepest_has_room(fc, off);
                fc->cur->off =+ off;
                fc->pos =+ off;

                return 0;

        case SEEK_END:
                break;
        default:
                HIERR("frag_curs_seek err: whence value unrecognized.");
                return -1;
        }
}



struct map_anchor *frag_curs_get_anchor( struct frag_curs *fc )
{
        struct hiena_frag *f;
        struct map_anchor *ma;
        int er;
        size_t pos;

        if( fc == NULL )
        {
                HIERR("frag_curs_get_anchor: err: fc NULL");
                return NULL;
        }

        f = frag_curs_find_deepest( fc );

        pos = fc->cur->off;

        ma = frag_get_anchor( f, pos );

        if( ma == NULL )
        {
                ma = map_anchor_new();
                if( ma == NULL )
                {
                        HIERR("frag_curs_get_anchor: err: ma NULL; couldn't allocate");
                        return NULL;
                }

                frag_put_anchor( f, pos, ma );
        }
        return ma;
}
