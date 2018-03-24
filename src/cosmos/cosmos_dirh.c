
#include <stdlib.h>
#include <sys/stat.h>
#include "../access_frame.h"
#include "../dcel.h"
#include "../btree_cpp.h"
#include "../hierr.h"
#include "cosmos_db.h"
#include "cosmos_dirh.h"



cosmos_dirh_t cosmos_opendir(struct cosmos *cm, cosmos_id_t af)
{
        (struct access_frame *)af;
        struct cosmos_dirh *dh;
        struct hiena_dcel *dc;
        btree_t *bt;

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

        dh->cosmos = cm;
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


/* from cosmos_readdir.md:

   for each in dcel's dname index
       apply aframe remappings
       expand string
       add to directory list
         
 */

struct cosmos_dirent *cosmos_readdir( cosmos_dirh_t dh )
{
        HIERR("cosmos_readdir");


        struct cosmo_dirent *e;
        btree_curs *curs;
        bval_t dirent_id;
        struct access_frame *af;


        if( dh == NULL )
        {
                HIERR("cosmos_readdir dh NULL");
                return NULL;
        }


        curs = dh->curs;



        if( curs == NULL )
        {
                HIERR("cosmos_readdir curs NULL");
                return NULL;
        }


        af = dh->aframe;


        if( af == NULL )
        {
                HIERR("cosmos_readdir af NULL");
                return NULL;
        }





        dirent_id = btree_curs_value(curs);

        if( dirent_id == BVAL_NULL )
        {
                HIERR("cosmos_readdir dirent_id BVAL_NULL");
                return NULL;
        }



        dirent_id_remap = aframe_remap_dirent_id( af, dirent_id );


        if( dirent_id_remap != BVAL_NULL )
        {
                dirent_id = dirent_id_remap;
        }



        d_name = cosmos_get_string( dirent_id );

        e = malloc(sizeof(*e));

        e->d_name;
        e->d_ino;

        return e;
}
