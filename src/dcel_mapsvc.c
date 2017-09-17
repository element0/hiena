





#include <stdlib.h>
#include "frag.h"
#include "frag_curs.h"
#include "dcel_fh.h"
#include "dcel_mapsvc.h"
#include "mapcel.h"
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
    warning:  this implementation does not accomodate dirents on the same mapanchor -- that is to say, if two grammar rules map to the same byte position.
 *
 */
int dcel_mapsvc_new_dirent( struct dcel_fh *dfh, struct hiena_mapcel *mc )
{
        if( dfh == NULL
         || mc == NULL )
        {
                HIERR("dcel_mapsvc_new_dirent: err: dfh or mc NULL");
                return -1;
        }
       
        struct map_anchor *ma;
        btree_t *bt;
        void *key;

        ma = mc->head_anchor;
        if( ma == NULL )
        {
                HIERR("dcel_mapsvc_new_dirent: warn: map anchor NULL. probably not what you want.");

        }

        key = (void *)ma;

        if( bt == NULL )
        {
                bt = btree_new();
                dfh->tmpdir = bt;
        }

        btree_put( bt, key, (void *)mc );

        return 0;
}

int dcel_mapsvc_new_dir(struct dcel_fh *dfh, struct hiena_mapcel *mc)
{
        if( dfh == NULL
         || mc == NULL )
        {
                HIERR("dcel_mapsvc_new_dir: err: dfh or mc NULL");
                return -1;
        }
        
        if( mc->dir != NULL )
        {
                HIERR("dcel_mapsvc_new_dir: warn: mc->dir NOT NULL. Previous directory struct may be lost.");
        }
        mc->dir = dfh->tmpdir;
        dfh->tmpdir = NULL;

        dfh->dcel->mapcel = mc;

        return 0;
}



struct dcel_mapsvc_ops dcel_mapsvc = {
        .new = dcel_mapsvc_new,
        .newterm = dcel_mapsvc_newterm,
        .add = dcel_mapsvc_add,
        .new_dirent = dcel_mapsvc_new_dirent,
        .new_dir = dcel_mapsvc_new_dir,
        .getenv = getenv,
};







