
#include <stdlib.h>
#include <sys/stat.h>
#include "../access_frame.h"
#include "../btree_cpp.h"
#include "../hierr.h"
#include "cosmos_db.h"
#include "cosmos_dirh.h"


cosmos_dirh_t cosmos_diropen( struct cosmos *cm, cosmos_id_t af )
{
        (struct access_frame *)af;

        if( cm == NULL )
        {
                HIERR("cosmos_diropen input cm NULL");
                return NULL;
        }

        void *dh;
        struct hiena_dcel *dc;
        btree_curs *curs;

        if( af == NULL )
        {
                HIERR("cosmos_diropen input af is NULL");
                return NULL;
        }

        dc = af->dcel;

        if( dc == NULL )
        {
                HIERR("cosmos_diropen af->dcel is NULL");
                return NULL;
        }

        index = dc->dir;

        if( index == NULL )
        {
                HIERR("cosmos_diropen dc->dir NULL");
                return NULL;
        }

        curs = btree_get_curs( index );

        if( curs == NULL )
        {
                HIERR("cosmos_diropen curs NULL");
                return NULL;
        }

        return (cosmos_dirh_t)curs;
}



cosmos_dirh_t cosmos_opendir(struct cosmos *cm, cosmos_id_t af)
{
        (struct access_frame *)af;
        struct cosmos_dirh *dh;
        struct hiena_dcel *dc;
        btree_t bt;

        if( cm == NULL || af == NULL )
        {
                HIERR("cosmos_opendir af or cm NULL");
                return NULL;
        }

        dc = af->dcel;

        if( dc == NULL )
        {
                HIERR("cosmos_opendir dcel NULL");
                return NULL;
        }

        bt = dc->dir;

        if( bt == NULL )
        {
                HIERR("cosmos_opendir dcel->dir NULL");
                return NULL;
        }

        malloc(sizeof(*dh));

        dh->cosmos_db = cm;
        dh->aframe = af;
        dh->curs = btree_get_curs( bt );

        return dh;
}

int cosmos_closedir( cosmos_dirh_t dh )
{
        if( dh == NULL )
        {
                HIERR("cosmos_closedir dh NULL");
                return -1;
        }

        btree_curs_cleanup( dh->curs );

        free(dh);

        return 0;
}
struct dirent *cosmos_readdir( cosmos_dirh_t dh )
{
        /* from cosmos_readdir.md:

           for each in dcel's dname index
           apply aframe remappings
           expand string
           add to directory list
         
         */

        struct dirent *e;
        btree_curs *curs;
        bval_t strid;

        curs = dh;

        if( curs == NULL )
        {
                HIERR("cosmos_readdir curs NULL");
                return NULL;
        }

        e = malloc(sizeof(*e));

        strid = btree_curs_value(curs);

        printf("cosmos_readdir\n");

        return e;
}
