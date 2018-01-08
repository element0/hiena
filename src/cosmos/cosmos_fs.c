#include <stdlib.h>
#include <sys/stat.h>
#include "cosmos_db.h"
#include "../access_frame.h"
#include "../btree_cpp.h"
#include "../hierr.h"

int cosmos_stat(struct cosmos *cm, cosmos_id_t id, struct stat *sb)
{
        printf("cosmos_stat\n");

        sb->st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO;
        sb->st_ino = (ino_t)id;

        return 0;
}

cosmos_id_t cosmos_lookup(struct cosmos *cm, cosmos_id_t par, char *s)
{
        printf("cosmos_lookup %s\n", s);
        return 0;
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



cosmos_id_t cosmos_mknod(struct cosmos *cm, cosmos_id_t par, char *d_name, mode_t mode, dev_t dev)
{
        (struct access_frame *)par;

        if( cm == NULL
         || par == NULL
         || d_name == NULL )
        {
                HIERR("cosmos_mknod: err: input cm, par or d_name NULL.");
                return NULL;
        }

        btree_t *br;
        cosmos_id_t key;
        struct access_frame *targ;

        br = par->branch;
        key = cosmos_string_put(cm, d_name);
        targ = btree_get(br, (bkey_t)key);

        if( targ != NULL )
        {
                HIERR("cosmos_mknod: err: EEXIST.");
                return NULL;
        }

        targ = aframe_new();
        btree_put(br, (bkey_t)key, (void *)targ);

        return targ;
}


cosmos_id_t cosmos_mknod_path(struct cosmos *cm, cosmos_id_t par, char *d_name, mode_t mode, dev_t dev)
{
        printf("cosmos_mknod_path\n");
        return 0;
}
