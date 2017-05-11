




#ifndef HIENA_FRAG_FH_H
#define HIENA_FRAG_FH_H

#include "frag.h"

#undef MYSVC_ADDR_INIT_PARMS
#define MYSVC_ADDR_INIT_PARMS struct hiena_frag *

#include "hiena_fh.h"
#include "frag_svc.h"

struct frag_fh {
    struct hiena_frag *frag;
    struct frag_fh *inner_fh;
    struct frag_fh *outer_fh;
    struct hiena_fh *mfrag_fh;
}

struct hiena_fh *frag_fh_open( struct hiena_frag * );
int frag_fh_close( struct hiena_fh * );


#endif /*! HIENA_FRAG_FH_H */
