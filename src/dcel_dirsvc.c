#include <string.h>
#include "dcel_dirh.h"
#include "dcel_dirent.h"
#include "dcel_dirsvc.h"
#include "dcel_svc.h"
#include "hierr.h"


#include "hash.h"
#define HASHFUNC(x) (void *)hash_sdbm(x)






struct dcel_dirh *dcel_dirsvc_open( struct hiena_dcel *dc)
{
        if( dc == NULL )
        {
                HIERR("dcel_dirsvc_open: err: dc NULL");
                return NULL;
        }

        struct dcel_dirh *dh;
        struct hiena_frag *f;
        struct frag_curs *fc;
        struct map_anchor *ma;

        dh = malloc(sizeof(*dh));
        memset(dh,0,sizeof(*dh));

        f = dc->frag;
        fc = frag_curs_new( f );
        ma = frag_curs_get_anchor( fc );

        dh->dcel = dc;
        dc->retain++;

        dh->frag_cursor = fc;
        dh->cur_mapanchor = ma;
        dh->pos = 0;
        dh->len = frag_get_length( f );
        dh->len_rem = dh->len - dh->pos;

        return dh;
}

int dcel_dirsvc_close( struct dcel_dirh *dh )
{
        if( dh == NULL )
        {
                HIERR("dcel_closedir: err: dh NULL");
                return -1;
        }

        struct hiena_dcel *dc;
        struct frag_curs *fc;

        dc = dh->dcel;
        fc = dh->frag_cursor;

        if( dc != NULL )
                dc->retain--;

        frag_curs_cleanup( fc );

        free( dh );

        return 0;
}

struct dcel_dirent  *dcel_dirsvc_read( struct dcel_dirh *dh )
{
        if( dh == NULL )
        {
                HIERR("dcel_dirsvc_read: err: dh NULL");
                return NULL;
        }
        
        struct map_anchor *ma;
        size_t pos, len, len_rem;
        btree_t *cn, *props;
        bnode_t *bn;
        void *k, *kres;
        struct hiena_mapcel *child;
        struct dcel_dirent *de;
        unsigned long d_name_id;
        char *d_name;
        ino_t d_ino;

        ma = dh->cur_mapanchor;
        if( ma == NULL )
        {
                HIERR("dcel_dirsvc_read: err: ma NULL");
                return NULL;
        }

        pos = dh->pos;
        len = dh->len;
        len_rem = len - pos;

        k = (void *)len_rem;

        cn = ma->children;
        if( cn == NULL )
        {
                HIERR("dcel_dirsvc_read: err: cn NULL");
                return NULL;
        }

        bn = cn->root;
        if( bn == NULL )
        {
                HIERR("dcel_dirsvc_read: err: bn NULL");
                return NULL;
        }

        child = (struct hiena_mapcel *)bnode_value_at_key_or_nearest_lesser( bn, k, &kres );


        props = child->children;

        d_name_id = HASHFUNC( "d_name" );

        name_cel = btree_get( props, d_name_id );

        d_name = "DCEL_BUFDUP( )"; 
        //-------- todo

        de = malloc(sizeof(*de));

        de->d_name = d_name;

        return de;
}

struct dcel_mapsvc_ops dcel_dirsvc = {
        .opendir = dcel_dirsvc_open,
        .closedir = dcel_dirsvc_close,
        .readdir = dcel_dirsvc_read, 
};
