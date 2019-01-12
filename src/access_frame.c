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


int aframe_set_parent(struct access_frame *af, struct access_frame *par)
{
        if(af == NULL)
        {
                HIERR("aframe_set_parent: af NULL");
                
                return -1;
        }

        af->parent = par;

        return 0;
}



struct iovec *aframe_get_value_iovec(struct access_frame *af)
{
        struct hiena_dcel *dc;
        struct iovec *iov;

        if( af == NULL )
        {
                HIERR("aframe_get_value_iovec af NULL");
                return NULL;
        }

        dc = af->dcel;
        iov = dcel_val_ptr(dc);


        return iov;
}


int aframe_set_value_ptr(struct access_frame *af, void *ptr)
{
        int er;
        struct hiena_dcel *dc;
        void *buf;
        size_t len;


        er = dcel_set_val( dc, ptr, sizeof(void *) );

        return er;
}



void *aframe_get_value_ptr(struct access_frame *af)
{
        struct hiena_dcel *dc;
        struct iovec *iov;
        void *ptr;

        if( af == NULL )
        {
                HIERR("aframe_get_value_ptr af NULL");
                return NULL;
        }

        dc = af->dcel;
        iov = dcel_val_ptr(dc);

        ptr = iov->iov_base;

        return ptr;
}



bval_t aframe_remap_dirent_id( struct access_frame *af, bval_t key )
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


struct access_frame *aframe_set_branch(struct access_frame *af, cosmos_strid_t id, struct access_frame *branch)
{
        struct access_frame *res;
        btree_t *bt;


        if( af == NULL )
        {
                HIERR("aframe_set_branch af NULL");

                return NULL;
        }


        bt = af->branch;

        if( bt == NULL )
        {
                HIERR("aframe_set_branch: bt NULL");

                return NULL;
        }


        res = (struct access_frame *)btree_put( bt, (bkey_t)id, (bval_t)branch );

        if(res != branch)
        {
                HIERR("aframe_set_branch: res and branch differ.");

                return NULL;
        }

        return res;
}

struct access_frame *aframe_get_branch(struct access_frame *af, cosmos_strid_t id)
{
        bval_t br;
        btree_t *bt;
        struct access_frame *res;



        if( af == NULL )
        {
                HIERR("aframe_get_branch af NULL");
                return NULL;
        }


        bt = af->branch;

        if( bt == NULL )
        {
                HIERR("aframe_get_branch: bt NULL");
                return NULL;
        }
        

        br = btree_get( bt, (bkey_t)id );

        res = (struct access_frame *)br;



        return res;
}
