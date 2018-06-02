#include <stdlib.h>
#include <sys/stat.h>
#include "../access_frame.h"
#include "../btree_cpp.h"
#include "../hierr.h"
#include "cosmos_db.h"
#include "cosmos_dirh.h"
#include "cosmos_string_db.h"







int cosmos_stat(struct cosmos *cm, cosmos_id_t id, struct stat *sb)
{
        (struct access_frame *)id;

        printf("cosmos_stat\n");

        sb->st_dev = id->st_dev;
        sb->st_ino = (ino_t)id;
        sb->st_mode = id->st_mode;
        sb->st_nlink = id->st_nlink;

        return 0;
}




cosmos_id_t cosmos_lookup(struct cosmos *cm, cosmos_id_t par, char *s)
{
        (struct access_frame *)par;

        struct access_frame *(*lookfn)(struct cosmos *, struct access_frame *, char *);

        struct access_frame *found;
        cosmos_strid_t strid;
        char *ssav;
        int err;


        if(par == NULL)
        {
                HIERR("cosmos_lookup: err: par NULL");

                return COSMOS_ID_NULL;
        }



        printf("cosmos_lookup cache branch %s\n", s);




        /* in sync */

            /* look in branches */

        strid = cosmos_string_id(s);

        found = aframe_get_branch(par, strid);



        /* if found */

        if( found != NULL )
                return (cosmos_id_t)found;




        /* run lookup module */


        printf("cosmos_lookup deligate func %s\n", s);


        if( par->parent == NULL )
        {
                HIERR("cosmos_lookup: err: par->parent NULL");
                return COSMOS_ID_NULL;
        }


        lookfn = par->parent->lookfn;

        found = lookfn(cm, par, s);

        aframe_set_branch(par, strid, found);


        return (cosmos_id_t)found;
}













cosmos_fh_t cosmos_open(struct cosmos *cm, cosmos_id_t id)
{
        printf("cosmos_open\n");
        return 0;
}




size_t cosmos_read(void *buf, size_t size, size_t num, cosmos_fh_t fh)
{
        printf("cosmos_read\n");
        return 0;
}





cosmos_id_t cosmos_ln(struct cosmos *cm, cosmos_id_t id, cosmos_id_t par, char *name)
{
        printf("cosmos_ln\n");

        return 0;
}




cosmos_id_t cosmos_mknod(struct cosmos *cm, cosmos_id_t par, char *name, mode_t mode, dev_t dev)
{
        (struct access_frame *)par;

        if( cm == NULL
         || par == NULL
         || name == NULL )
        {
                HIERR("cosmos_mknod: err: input cm, par or name NULL.");
                return NULL;
        }

        btree_t *br;
        cosmos_strid_t key;
        struct access_frame *targ;

        br = par->branch;

        key = cosmos_put_string(cm, name);
        targ = (struct access_frame *)btree_get(br, (bkey_t)key);

        if( targ != NULL )
        {
                HIERR("cosmos_mknod: err: EEXIST.");
                return NULL;
        }

        targ = aframe_new();
        btree_put(br, (bkey_t)key, (bval_t)targ);

        targ->st_dev = dev;
        targ->st_mode = mode;
        targ->st_nlink = 1;
        targ->parent = par;

        return targ;
}





cosmos_id_t cosmos_mknod_path(struct cosmos *cm, cosmos_id_t par, char *path, mode_t mode, dev_t dev)
{
        printf("cosmos_mknod_path\n");
        return 0;
}





cosmos_id_t cosmos_mkdir(struct cosmos *cm, cosmos_id_t par, char *name, mode_t mode)
{
        printf("cosmos_mkdir\n");
        return cosmos_mknod(cm, par, name, mode | S_IFDIR, 0);
}
