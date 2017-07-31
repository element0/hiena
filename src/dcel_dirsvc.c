#include "dcel_dirh.h"
#include "dcel_dirsvc.h"
#include "dcel_svc.h"








struct dcel_dirh *dcel_dirsvc_open( struct hiena_dcel *dc)
{
        if( dc == NULL )
        {
                HIERR("dcel_dirsvc_open: err: dc NULL");
                return NULL;
        }

        struct dcel_dirh *dh;

        dh = malloc(sizeof(*dh));

        dh->dcel = dc;
        dc->retain++;

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
};