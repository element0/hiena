
/* 2018-05-08 0717 */
/* dcel_dirsvc */
/* opens and reads a linked list */



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
        struct dcel_dirent *cur;
        



        cur = dc->child_list;



        dh = malloc(sizeof(*dh));
        memset(dh,0,sizeof(*dh));

        dh->dcel = dc;
        dc->retain++;


        dh->cur = cur;
        dh->cur_ord = NULL;


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

struct dcel_dirent  *dcel_dirsvc_read( struct dcel_dirh *dh )
{
        if( dh == NULL )
        {
                HIERR("dcel_dirsvc_read: err: dh NULL");

                return NULL;
        }
        
        struct dcel_dirent *cur;

        cur = dh->cur;

        if( cur = NULL )
        {
                HIERR("dcel_dirsvc_read: alert: cur NULL:  EOF");

                return NULL;
        }

        dh->cur = cur->next;

        return cur;
}


struct dcel_mapsvc_ops dcel_dirsvc = {
        .opendir = dcel_dirsvc_open,
        .closedir = dcel_dirsvc_close,
        .readdir = dcel_dirsvc_read, 
};
