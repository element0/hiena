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

cosmos_id_t cosmos_lookup(struct cosmos *cm, cosmos_id_t par, char *s)
{
        printf("cosmos_lookup %s\n", s);

        if(par == NULL)
        {
                HIERR("cosmos_lookup: err: par NULL");
                return 0;
        }

        btree_t *br;
        cosmos_id_t strhash;
        cosmos_id_t found;


        br = par->branch;
        if( br == NULL )
        {
                HIERR("cosmos_lookup: err: br NULL");
                return 0;
        }

        strhash = cosmos_hash(s);

        found = (cosmos_id_t)btree_get(br, (bkey_t)strhash);
        
        return found;
}

struct dirent *cosmos_readdir( cosmos_dirh_t dir )
{
        printf("cosmos_readdir\n");
        return NULL;
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

cosmos_id_t cosmos_ln(struct cosmos *cm, cosmos_id_t id, cosmos_id_t id2)
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
