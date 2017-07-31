#ifndef HIENA_MAPCEL_H
#define HIENA_MAPCEL_H

#include <stdlib.h>
#include "frag.h"
#include "map_anchor.h"





struct hiena_mapcel {
        struct hiena_mapcel *next;
        struct hiena_mapcel *prev;
        int ruleid;
        size_t len;
        struct map_anchor *head_anchor;
        struct map_anchor *tail_anchor;
        struct hiena_frag *frag;
        btree_t *children;
};

struct hiena_mapcel *mapcel_new(int, size_t);

int mapcel_cleanup( struct hiena_mapcel * );



#endif /* !HIENA_MAPCEL_H */