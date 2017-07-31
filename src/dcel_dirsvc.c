#include "dcel_dirh.h"
#include "dcel_dirsvc.h"
#include "dcel_svc.h"
#include "hierr.h"








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

        dc = dh->dcel;

        if( dc != NULL )
                dc->retain--;

        free( dh );

        return 0;
}

struct dirent *dcel_dirsvc_read( struct dcel_dirh *dh )
{
        if( dh == NULL )
        {
                HIERR("dcel_dirsvc_read: err: dh NULL");
                return NULL;
        }

        
        struct dirent *de;

        de = NULL;

        return de;
}

struct dcel_mapsvc_ops dcel_dirsvc = {
        .opendir = dcel_dirsvc_open,
        .closedir = dcel_dirsvc_close,
        .readdir = dcel_dirsvc_read, 
};
