#ifndef HIENA_MAP_ANCHOR_H
#define HIENA_MAP_ANCHOR_H



/**
 * map_anchor are anchored to frags
 */



#include <stdlib.h>
#include "btrees.h"
#include "frag.h"



struct map_anchor
{
        btree_t *id_head;
        btree_t *id_tail;
        btree_t *children;
        struct map_anchor *next;
        size_t next_off;
        struct hiena_frag *frag;

};

struct map_anchor *map_anchor_new();
int map_anchor_cleanup ( struct map_anchor * );

struct ma_seek_result *ma_seek( struct map_anchor * );

#endif /*! HIENA_MAP_ANCHOR_H */