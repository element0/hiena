#ifndef HIENA_MAPCEL_H
#define HIENA_MAPCEL_H

#include <stdlib.h>
#include "frag.h"
#include "map_anchor.h"
#include "mapcel_dir.h"
#include "ptr_stack.h"



struct hiena_mapcel {
        void *ruleid;
        size_t len;

        /**
           relative to a frag
         */
        size_t off_head;

        struct map_anchor *head_anchor;
        struct map_anchor *tail_anchor;

        ptr_stack_t children;

        /* depricate? */
        struct hiena_mapcel *next;
        struct hiena_mapcel *prev;
};

struct hiena_mapcel *mapcel_new(char *, size_t);

int mapcel_cleanup( struct hiena_mapcel * );



#endif /* !HIENA_MAPCEL_H */
