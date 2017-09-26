#include <stdlib.h>
#include "mapcel.h"
#include "hierr.h"

struct hiena_mapcel *mapcel_new(char *ruleid, size_t len)
{
        struct hiena_mapcel *mc;

        mc = malloc(sizeof(*mc));
        if(mc == NULL)
        {
                HIERR("mapcel_new: malloc NULL");
                return NULL;
        }

        mc->len = len;
        mc->ruleid = ruleid;
        mc->children = NULL;

        return mc;
}

int mapcel_cleanup( struct hiena_mapcel *mc )
{
        btree_t *cn;
        struct mapcel_dir *d;

        if( mc == NULL )
        {
                HIERR("mapcel_cleanup: input mc NULL");
                return -1;
        }

        cn = mc->children;
        d = mc->dir;

        if( cn != NULL )
        {
                btree_cleanup( cn );
        }

        if( dir != NULL )
        {
                mapcel_dir_cleanup( d );
        }


        free(mc);
        return 0;
        
}

int mapcel_add ( struct hiena_mapcel *par, struct hiena_mapcel *chi )
{
        btree_t *cn;
        void *key;
        void *val;
        struct map_anchor *ha;

        cn = par->children;

        if( cn == NULL )
                cn = btree_new();

        ha = chi->head_anchor;

        key = (void *)ha;
        val = (void *)chi;

        btree_put( cn, key, val );
        if( par->head_anchor == NULL )
                par->head_anchor = ha;
        par->tail_anchor = chi->tail_anchor;

        return 0;
}