




#ifndef HIENA_MAPCEL_FH_H
#define HIENA_MAPCEL_FH_H

#include "frag.h"
#include "hiena_fh.h"

struct mapcel_fh {
    struct hiena_mapcel *mapcel;
    size_t off;
    int is_eof;
    const char *mode;
    struct frag_fh *frag_fh;
};

struct mapcel_fh *mapcel_fh_new();

int mapcel_fh_cleanup( struct mapcel_fh * );


#endif /*! HIENA_MAPCEL_FH_H */
