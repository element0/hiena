




#ifndef HIENA_MFRAG_FH_H
#define HIENA_MFRAG_FH_H

#include "mfrag.h"
#include "hiena_fh.h"

struct mfrag_fh {
        struct hiena_mfrag *mfrag;
        struct hiena_fh *src_fh;
        void *srcfh;
        off_t pos;
        int is_eof;
};

struct mfrag_fh *mfrag_fh_new();
int mfrag_fh_cleanup( struct mfrag_fh * );


#endif /*! HIENA_MFRAG_FH_H */
