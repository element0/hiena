#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "../access_frame.h"
#include "../btree_cpp.h"
#include "../hierr.h"
#include "../ptr_stack.h"
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
        targ->lookfn = par->lookfn;

        return targ;
}





cosmos_id_t cosmos_mknod_path(struct cosmos *cm, cosmos_id_t par, char *pathstr, mode_t mode, dev_t dev)
{
        printf("cosmos_mknod_path\n");

        char *path, *cur, *last;
        mode_t mode2;
        cosmos_id_t par2;
        size_t slen;

        slen = strlen(pathstr);
        path = strndup(pathstr, slen);

        cur = strtok(path, "/");
        par2 = par;

        while(cur != NULL)
        {
                printf("%s\n",cur);
                last = cur;
                cur = strtok(NULL, "/");
                if(cur != NULL)
                        mode2 = mode | S_IFDIR;
                par2 = cosmos_mknod(cm, par2, last, mode2, 0);

        }

        free(path);

        return par2;
}





cosmos_id_t cosmos_mkdir(struct cosmos *cm, cosmos_id_t par, char *name, mode_t mode)
{
        printf("cosmos_mkdir\n");
        return cosmos_mknod(cm, par, name, mode | S_IFDIR, 0);
}
