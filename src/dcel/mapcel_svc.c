




#include <stdlib.h>
#include "hiena_svc.h"
#include "mapcel.h"
#include "mapcel_fh.h"
#include "hierr.h"


void *mapcel_svc_open( void *addr, const char *mode)
{
        struct hiena_mapcel *mc;
        struct mapcel_fh *h;

        mc = (struct hiena_mapcel *)addr;
        if( mc == NULL )
        {
                 HIERR("mapcel_svc_open: err input mc NULL");

        }



        h = mapcel_fh_new();
        if( h == NULL )
        {
                 HIERR("mapcel_svc_open: err mapcel_fh_new() NULL");
                return h;
        }

        return h;
}

int mapcel_svc_close( void *fp )
{
        struct mapcel_fh *h;

        h = (struct mapcel_fh *)fp;
        if( h == NULL )
        {
                 HIERR("mapcel_svc_close: err input h NULL");
                return -1;
        }

        mapcel_fh_cleanup( h );

        return 0;
}

int mapcel_svc_seek( void *fp, long offset, int whence )
{

        return 0;
}

int mapcel_svc_getchar( void *fp )
{
        struct mapcel_fh *h;

        h = (struct mapcel_fh *)fp;
        if( h == NULL )
        {
                 HIERR("mapcel_svc_getchar: err input h NULL");
                return 0;
        }

        return 0;
}

size_t mapcel_svc_read( void *ptr, size_t size, size_t nmemb, void *fp )
{
        struct mapcel_fh *h;

        h = (struct mapcel_fh *)fp;
        if( h == NULL )
        {
                 HIERR("mapcel_svc_read: err input h NULL");
                return 0;
        }

        return 0;
}

size_t mapcel_svc_write( void *ptr, size_t size, size_t nmemb, void *fp )
{
        return 0;
}




struct hiena_svc mapcel_svc_ops = {
        .read  = mapcel_svc_read,
        .write = mapcel_svc_write,
        .open  = mapcel_svc_open,
        .close = mapcel_svc_close,
        .seek  = mapcel_svc_seek,
        .getchar = mapcel_svc_getc,
};



