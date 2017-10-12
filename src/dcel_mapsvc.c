





#include <stdlib.h>
#include "frag.h"
#include "frag_curs.h"
#include "dcel_fh.h"
#include "dcel_mapsvc.h"
#include "mapcel.h"
#include "mapcel_dir.h"
#include "hierr.h"
#include "btrees.h"

#include "hash.h"
#define HASHFUNC(x) hash_sdbm(x)


int dcel_mapsvc_ptrcmp( void *p1, void *p2 )
{
        return 0;
}

int dcel_mapsvc_idcmp( void *id1, void *id2 )
{
        return 0;
}


struct hiena_mapcel *dcel_mapsvc_new(void *p)
{
        size_t len;
        char *s;
        unsigned long ruleid;
        struct hiena_mapcel *mc;

        len = 0;

        s = (char *)p;
        ruleid = HASHFUNC( s );

        mc = mapcel_new( (void *)ruleid, len);

        if( mc == NULL )
        {
                HIERR("dcel_mapsvc_new: err: can't make new mapcel");
                return NULL;
        }

        return mc;
}


struct hiena_mapcel *dcel_mapsvc_newterm( struct dcel_fh *dfh, void *p, size_t pos, size_t len)
{
        if( dfh == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: dfh is NULL");
                return NULL;
        }

        if( p == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: p is NULL");
                return NULL;
        }

        struct frag_curs *fc;
        struct hiena_mapcel *mc;
        struct map_anchor *mh;
        struct map_anchor *mt;
        char *s;
        unsigned long ruleid;
        size_t old_pos, off;


        fc = dfh->fcurs;

        if( fc == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: dcel file handle's frag cursor is NULL");
                return NULL;
        }

        old_pos = fc->pos;

        off = pos - old_pos;

        frag_curs_seek( fc, off, SEEK_CUR );
        if( frag_curs_find_deepest_has_room( fc, len ) == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: mapping out of bounds for dcel");
                return NULL;
        }

        s = (char *)p;

        ruleid = HASHFUNC( s );

        mc = mapcel_new((void *)ruleid, len);

        if( mc == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: can't make new mapcel");
                return NULL;
        }


        mh = frag_curs_get_anchor( fc );

        if( mh == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: can't get head anchor");

                goto abort_mapcel;
        }

        map_anchor_add( mh, mc );

        frag_curs_seek( fc, len, SEEK_CUR );
        mt = frag_curs_get_anchor( fc );

        if( mt == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: can't get tail anchor");
                map_anchor_cleanup( mh );
                goto abort_mapcel;
        }

        map_anchor_add_tail( mt, mc );

        return mc;

abort_mapcel:
        mapcel_cleanup( mc );
        return NULL;
}


int dcel_mapsvc_grow(void *p, size_t len)
{
        if( p == NULL )
        {
                HIERR("dcel_mapsvc_grow: err: p is NULL");
                return -1;
        }
        return 0;
}

int dcel_mapsvc_add( struct hiena_mapcel *par, struct hiena_mapcel *chi )
{
        if( par == NULL
         || chi == NULL )
        {
                HIERR("dcel_mapsvc_add: err: par or chi NULL");
                return -1;
        }

        btree_t *cn;
        void *key;
        void *val;
        struct map_anchor *ha;
        void *id;

        cn = par->children;

        if( cn == NULL )
                cn = btree_new();

        ha = chi->head_anchor;
        id = chi->ruleid;

        if( ha == NULL )
        {
                HIERR("dcel_mapsvc_add: err: child's head anchor is NULL");
                return -1;
        }

        key = (void *)ha;
        val = (void *)chi;

        btree_put( cn, key, val );

        if( par->head_anchor == NULL )
                par->head_anchor = ha;

        par->tail_anchor = chi->tail_anchor;

        par->len =+ chi->len;

        return 0;
}


/**
    update (9/22/2017):
    implements a simple variable length array as a directory.
 */
int dcel_mapsvc_new_dirent( struct dcel_fh *dst, struct hiena_mapcel *mc )
{
        if( dst == NULL
         || mc == NULL )
        {
                HIERR("dcel_mapsvc_new_dirent: err: dst or mc NULL");
                return -1;
        }

        ptr_stack_t dstack;
        struct mapcel_dir *d;

        dstack = dst->dir_stack;

        if( dstack == NULL )
        {
                dstack = ptr_stack_new();
                dst->dir_stack = dstack;
                d = mapcel_dir_new();
                ptr_stack_push( dstack, (void *)d );

        }else{

                d = (struct mapcel_dir *)ptr_stack_top(dstack);
                if( d == NULL )
                {
                        d = mapcel_dir_new();
                        ptr_stack_push( dstack, (void *)d );
                }
        }

        if( mapcel_dir_add(d, mc) == -1 )
        {
                HIERR("dcel_mapsvc_new_dirent: can't add dirent.");
                return -1;
        }

        return 0;
}

int dcel_mapsvc_start_dir(struct dcel_fh *dst)
{
        if( dst == NULL )
        {
                HIERR("dcel_mapsvc_start_dir: err: dst or mc NULL");
                return -1;
        }

        ptr_stack_t dstack;
        struct mapcel_dir *d;

        dstack = dst->dir_stack;
        d = mapcel_dir_new();

        if( dstack == NULL )
        {
                dstack = ptr_stack_new();
                dst->dir_stack = dstack;
        }

                ptr_stack_push( dstack, (void *)d );
       
        return 0;
}

int dcel_mapsvc_finish_dir( struct dcel_fh *dst, struct hiena_mapcel *mc )
{
        if( dst == NULL
         || mc == NULL )
        {
                HIERR("dcel_mapsvc_finish_dir: err: dat or mc NULL");
                return -1;
        }

        ptr_stack_t dstack;
        struct mapcel_dir *d;

        dstack = dst->dir_stack;
        if( dstack == NULL )
        {
                HIERR("dcel_mapsvc_finish_dir: err: dstack NULL.");
                return -1;
        }

        d = (struct mapcel_dir *)ptr_stack_top( dstack );
        
        if( mc->dir != NULL )
        {
                HIERR("dcel_mapsvc_finish_dir: warn: mc->dir NOT NULL. Previous directory struct may be lost.");
        }
        mc->dir = d;
        ptr_stack_pop( dstack );

        return 0;
}


int dcel_mapsvc_finish(struct dcel_fh *dst, struct hiena_mapcel *mc)
{
        if( dst == NULL
         || mc == NULL )
        {
                HIERR("dcel_mapsvc_finish: err: input dst or mc NULL");
                return -1;
        }

        struct hiena_dcel *dc;

        dc = dst->dcel;

        if( dc == NULL )
        {
                HIERR("dcel_mapsvc_finish: err: dc NULL");
                return -1;
        }

        dc->mapcel = mc;

        return 0;
}

struct dcel_mapsvc_ops dcel_mapsvc = {
        .new = dcel_mapsvc_new,
        .newterm = dcel_mapsvc_newterm,
        .add = dcel_mapsvc_add,
        .new_dirent = dcel_mapsvc_new_dirent,
        .start_dir = dcel_mapsvc_start_dir,
        .finish_dir = dcel_mapsvc_finish_dir,
        .finish = dcel_mapsvc_finish,
        .getenv = getenv,
};







