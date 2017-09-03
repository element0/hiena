#ifndef HIENA_MAPCEL_H
#define HIENA_MAPCEL_H

#include <stdlib.h>
#include "frag.h"
#include "map_anchor.h"





struct hiena_mapcel {
        void *ruleid;
        size_t len;
        struct map_anchor *head_anchor;
        struct map_anchor *tail_anchor;
        btree_t *children;
        btree_t *dir;

/* depricate? */
        struct hiena_mapcel *next;
        struct hiena_mapcel *prev;
        struct hiena_frag *frag;
};

struct hiena_mapcel *mapcel_new(char *, size_t);

int mapcel_cleanup( struct hiena_mapcel * );



#endif /* !HIENA_MAPCEL_H */
