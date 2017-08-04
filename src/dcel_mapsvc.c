





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

        struct frag_curs *fc;
        struct hiena_mapcel *mc;
        struct map_anchor *mh;
        struct map_anchor *mt;
        char *s;
        unsigned long ruleid;


        fc = dfh->fcurs;
        if( fc == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: dcel file handle's frag cursor is NULL");
                return NULL;
        }

        if( frag_curs_find_deepest_has_room( fc, len ) != 0 )
        {
                HIERR("dcel_mapsvc_newterm: err: mapping out of bounds for dcel");
                return NULL;
        }

        s = (char *)p;
        ruleid = HASHFUNC( s );
        mc = mapcel_new((void *)ruleid,len);

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

        frag_curs_seek( fc, len, SEEK_CUR );
        mt = frag_curs_get_anchor( fc );

        if( mt == NULL )
        {
                HIERR("dcel_mapsvc_newterm: err: can't get tail anchor");
                map_anchor_cleanup( mh );
                goto abort_mapcel;
        }

        mc->head_anchor = mh;
        mc->tail_anchor = mt;

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

        btree_t *cn, *cn_id;
        void *key;
        void *val;
        struct map_anchor *ha;
        void *id;

        cn = par->children;
        cn_id = par->child_ids;

        if( cn == NULL )
                cn = btree_new();

        if( cn_id == NULL )
                cn_id = btree_new();

        ha = chi->head_anchor;
        id = chi->ruleid;

        if( ha == NULL )
        {
                HIERR("dcel_mapsvc_add: err: ha NULL");
                return -1;
        }

        key = (void *)ha;
        val = (void *)chi;

        btree_put( cn, key, val );

        key = (void *)id;
        val = (void *)chi;

        btree_put( cn_id, key, val );


        if( par->head_anchor == NULL )
                par->head_anchor = ha;
        par->tail_anchor = chi->tail_anchor;

        return 0;
}

int dcel_mapsvc_add_dirent( struct hiena_mapcel *par, struct hiena_mapcel *chi )
{
        struct map_anchor *ha;
        btree_t *cn;
        size_t len;

        dcel_mapsvc_add( par, chi );

        ha = chi->head_anchor;
        cn = ha->children;
        len = chi->len;

        btree_put( cn, (void *)len, (void *)chi );
        
        return 0;
}

struct dcel_mapsvc_ops dcel_mapsvc = {
        .new = dcel_mapsvc_new,
        .newterm = dcel_mapsvc_newterm,
        .add = dcel_mapsvc_add,
        .add_dirent = dcel_mapsvc_add_dirent,
};







