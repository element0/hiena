#include <string.h>
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
        ffh->mfrag = NULL;
}

static void frag_curs_node_cleanup( struct frag_fh *ffh )
{
        frag_fh_cleanup( ffh );
}



struct frag_curs *frag_curs_new( struct hiena_frag *f )
{
        struct frag_curs *fc;
        struct frag_fh *ffh;

        ffh = frag_curs_node_new(f);
        ffh->outer_fh = ffh;


        fc = malloc(sizeof(*fc));
        memset(fc, 0, sizeof(*fc));
        fc->f = f;
        fc->root = ffh;
        fc->cur = ffh;

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

        cursav = fc->cur;

        cur = frag_curs_node_new(f);
        cur->outer_fh = cursav;
        cur->off = new_off;

        cursav->inner_fh = cur;

        fc->cur = cur;

        return 0;
}

int frag_curs_step_outward( struct fragcurse *fc )
{
        if( fc == NULL )
        {
                HIERR("frag_curs_step_out: err: fc NULL";
                return -1;
        }

        struct frag_fh *cur;
        struct frag_fh *outer;
        size_t off;

        cur = fc->cur;

        if( cur == fc->root )
        {
                HIERR("frag_curs_step_out: err: cur is root, can't step out.";
                return -2;
        }

        outer = cur->outer_fh;

        if( cur == outer )
        {
                HIERR("frag_curs_step_out: err: cur is outer, can't step out.";
                return -3;
        }

        off = outer->off + cur->off;
        outer->off = off;

        fc->cur = outer;

        frag_curs_node_cleanup(cur);

        return 0;
}


struct hiena_frag *frag_curs_find_deepest_has_room( struct frag_curs *fcurs, size_t len )
{
        struct hiena_frag *f, cf;
        size_t off, new_off;
        bnode_t n;

        f = fcurs->frag;
        off = fcurs->off;


        if( frag_has_room( f, len ))
                goto find_child;
        else
                goto find_parent;

find_child:

        cf = (struct hiena_frag *) bnode_value_at_key_or_nearest_lesser(f->children, off, &new_off);

        if(frag_has_room( cf, len ))
        {
                
frag_curs_step_into( fcurse, cf, new_off );
                f = cf;
                off = new_off;
                goto find_child;
        }

        return f;

find_parent:

        switch(frag_curs_step_outward(fcurse))
       {
        case -1:
                HIERR("frag_curs_find_deepest_has_room: improbable: parent null");
                return -1;
        case -2:
                HIERR("frag_curs_find_deepest_has_room: frag has no parent and no room");
                return -1;
        case -3:
                HIERR("frag_curs_find_deepest_has_room: improbable: frag has no parent ");
                return -1;
        default:
                break;
        }

        f = fcurse->frag;

        if(!frag_has_room( f, len ))
               goto find_parent;

        return f;
}

struct hiena_frag *frag_curs_find_deepest( struct frag_curs *fcurs )
{
        return frag_curs_find_deepest_has_room( fc, 0 );
}


int frag_curs_seek( struct frag_curs *fc, size_t off, int whence)
{
        if( fc == NULL )
        {
                HIERR("frag_curs_seek err: fc NULL";
                return -1;
        }

        fc->cur->off =+ off;

        return 0;
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
