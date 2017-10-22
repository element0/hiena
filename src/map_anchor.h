#ifndef HIENA_MAP_ANCHOR_H
#define HIENA_MAP_ANCHOR_H



/**
 * map_anchor are anchored to frags
 */



#include <stdlib.h>
#include "btrees.h"
#include "frag.h"

struct hiena_mapcel;


struct map_anchor
{
        btree_t *id_head;
        btree_t *id_tail;
        btree_t *children;

        /* convenience */
        struct map_anchor *next;
        size_t next_off;

        /* deprecate */
        struct hiena_frag *frag;
};

struct map_anchor *map_anchor_new();

int map_anchor_cleanup ( struct map_anchor * );

int map_anchor_add( struct map_anchor *, struct hiena_mapcel * );

int map_anchor_add_tail( struct map_anchor *, struct hiena_mapcel * );

#endif /*! HIENA_MAP_ANCHOR_H */