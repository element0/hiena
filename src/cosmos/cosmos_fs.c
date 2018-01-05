#include <stdlib.h>
#include <sys/stat.h>
#include "cosmos_db.h"
#include "../access_frame.h"
#include "../btree_cpp.h"
#include "../hierr.h"



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
