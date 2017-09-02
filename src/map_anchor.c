





#include <stdlib.h>
#include "map_anchor.h"
#include "mapcel.h"
#include "hierr.h"


struct map_anchor *map_anchor_new()
{
        struct map_anchor *ma;

        ma = malloc(sizeof(*ma));

        return ma;
}

int map_anchor_cleanup( struct map_anchor *ma )
{
        if( ma == NULL )
		return -1;

	free( ma );

	return 0;
}


int map_anchor_add( struct map_anchor *ma, struct hiena_mapcel *mc )
{
        if( ma == NULL
         || mc == NULL )
        {
                HIERR("map_anchor_add: ma or mc NULL");

                return -1;
        }

        btree_t *tr;
        void *id;
        
        tr = ma->id_head;

        if( tr == NULL )
        {
                HIERR("map_anchor_add: tr NULL");
                return -1;
        }

        id = mc->ruleid;

        btree_put( tr, id, (void *)mc );

        mc->head_anchor = ma;

        return 0;
}


int map_anchor_add_tail( struct map_anchor *ma, struct hiena_mapcel *mc )
{
        if( ma == NULL
         || mc == NULL )
        {
                HIERR("map_anchor_add_tail: ma or mc NULL");

                return -1;
        }

        btree_t *tr;
        void *id;
        
        tr = ma->id_tail;

        if( tr == NULL )
        {
                HIERR("map_anchor_add_tail: tr NULL");
                return -1;
        }

        id = mc->ruleid;

        btree_put( tr, id, (void *)mc );

        mc->tail_anchor = ma;


        return 0;
}


