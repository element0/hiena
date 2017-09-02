




#ifndef HIENA_FRAG_FH_H
#define HIENA_FRAG_FH_H

#include "frag.h"
#include "hiena_fh.h"

struct frag_fh {
    struct hiena_frag *frag;
    size_t off;
    int is_eof;
    const char *mode;
    struct frag_fh *inner_fh;
    struct frag_fh *outer_fh;
    struct mfrag_fh *mfrag_fh;
};

struct frag_fh *frag_fh_new();
int frag_fh_cleanup( struct frag_fh * );


#endif /*! HIENA_FRAG_FH_H */
