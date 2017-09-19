





#include <stdlib.h>
#include <string.h>
#include "map_anchor.h"
#include "mapcel.h"
#include "hierr.h"


struct map_anchor *map_anchor_new()
{
        struct map_anchor *ma;

        ma = malloc(sizeof(*ma));
        memset(ma,0,sizeof(*ma));

        ma->id_head = btree_new();
        ma->id_tail = btree_new();

        return ma;
}

int map_anchor_cleanup( struct map_anchor *ma )
{
        if( ma == NULL )
                return -1;

        if( ma->id_head != NULL )
                btree_cleanup( ma->id_head );

        if( ma->id_head != NULL )
                btree_cleanup( ma->id_head );


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

        btree_t *b;
        void *id;
        
        b = ma->id_head;

        if( b == NULL )
        {
                HIERR("map_anchor_add: b NULL");
                return -1;
        }

        id = mc->ruleid;

        btree_put( b, id, (void *)mc );

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

        btree_t *b;
        void *id;
        
        b = ma->id_tail;

        if( b == NULL )
        {
                HIERR("map_anchor_add_tail: b NULL");
                return -1;
        }

        id = mc->ruleid;

        btree_put( b, id, (void *)mc );

        mc->tail_anchor = ma;


        return 0;
}


