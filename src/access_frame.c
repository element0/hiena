#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include "access_frame.h"
#include "btree_cpp.h"
#include "hierr.h"
#include "dcel.h"


struct access_frame *aframe_new()
{
        struct access_frame *af;

        af = malloc(sizeof(*af));
        memset(af,0,sizeof(*af));

        af->branch = btree_new();

        return af;
}


struct access_frame *aframe_spawn(struct access_frame *par)
{
        struct access_frame *af;

        if(par == NULL)
        {
                HIERR("aframe_spawn: par NULL");
                return NULL;
        }

        af = aframe_new();
        if(af == NULL)
        {
                HIERR("aframe_spawn: af NULL");
                return NULL;
        }


        /* inherit */
        
        af->lookfn = par->lookfn;
        af->parent = par;

        return af;
}



int aframe_cleanup( struct access_frame *af )
{
        if( af == NULL )
        {
                HIERR("aframe_cleanup called on a NULL ptr");
                return -1;
        }
        btree_cleanup( af->branch );
        free( af );

        return 0;
}


struct iovec *aframe_get_value_ptr(struct access_frame *af)
{
        struct hiena_dcel *dc;
        struct iovec *iov;

        if( af == NULL )
        {
                HIERR("aframe_remap_dirent_id af NULL");
                return NULL;
        }

        dc = af->dcel;
        iov = dcel_val_ptr(dc);


        return iov;
}


bval_t  aframe_remap_dirent_id( struct access_frame *af, bval_t key )
{
        bval_t res;
        btree_t *bt;



        if( af == NULL )
        {
                HIERR("aframe_remap_dirent_id af NULL");
                return BVAL_NULL;
        }
        



        bt = af->remap;

        if( bt == NULL )
        {
                HIERR("aframe_remap_dirent_id bt NULL");
                return BVAL_NULL;
        }
        



        res = btree_get( bt, (bkey_t)key );

        return res;
}


struct access_frame *aframe_set_branch(struct access_frame *par, cosmos_strid_t id, struct access_frame *branch)
{
          return NULL;
}

struct access_frame *aframe_get_branch(struct access_frame *par, cosmos_strid_t id)
{
          return NULL;
}
