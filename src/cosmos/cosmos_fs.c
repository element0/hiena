#include <stdlib.h>
#include <sys/stat.h>
#include "cosmos_db.h"
#include "../access_frame.h"
#include "../btree_cpp.h"
#include "../hierr.h"





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




cosmos_id_t cosmos_lookup(struct cosmos *cm, cosmos_id_t frame, char *s)
{
        (struct access_frame *)frame;

        struct access_frame *(*lookfn)(struct cosmos *, struct access_frame *, char *);

        struct access_frame *(*ilookfn)(struct cosmos *, struct access_frame *, char *);

        struct access_frame *found;
        cosmos_id_t strid;
        cosmos_id_t strid2;
        char *ssav;



        strid = cosmos_string_id(s);


        printf("cosmos_lookup (before remap) %s\n", s);



        /* look in branches */

        found = aframe_get_branch(frame, strid);

        if( found != NULL )
                return (cosmos_id_t)found;



        /* look in remap */

        strid2 = aframe_get_remap_targ(frame, strid);

        if( strid2 != 0 )
        {
                ssav = s;
                stridsav = strid;
                s = cosmos_get_string(cm, strid2);
                strid = strid2;
        }




        /* run lookup module */


        printf("cosmos_lookup (after remap) %s\n", s);

        if(frame == NULL)
        {
                HIERR("cosmos_lookup: err: frame NULL");
                return 0;
        }

        if( frame->parent == NULL )
        {
                HIERR("cosmos_lookup: err: frame->parent NULL");
                return 0;
        }



        

        lookfn = frame->parent->lookfn;

        ilookfn = lookfn( cm, frame, ".cosm/lookup/cosmos_lookup_fn" );

        frame->lookfn = ilookfn;


        found = ilookfn( cm, frame, s );
        
        
        aframe_set_branch(frame, strid, found);


        return (cosmos_id_t)found;
}



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
        cosmos_id_t key;
        struct access_frame *targ;

        br = par->branch;

        key = cosmos_string_put(cm, name);
        targ = btree_get(br, (bkey_t)key);

        if( targ != NULL )
        {
                HIERR("cosmos_mknod: err: EEXIST.");
                return NULL;
        }

        targ = aframe_new();
        btree_put(br, (bkey_t)key, (void *)targ);

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
