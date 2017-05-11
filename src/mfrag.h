





#ifndef HIENA_MFRAG_H
#define HIENA_MFRAG_H

#include <sys/types.h>
#define HIMFRAG_BOUND_T off_t
#define HIMFRAG_BOUNDS_MIN 0
#define HIMFRAG_BOUNDS_MAX 2147483648
#define HIMFRAG_BOUND_ERR 0

#define HIMFRAG_BUFSIZE_T size_t
/* 2017-03-24 pos and off should match */
#define HIMFRAG_POS_T off_t
#define HIMFRAG_OFF_T off_t
#define HIMFRAG_OFF_MIN 0
#define HIMFRAG_OFF_MAX (2^31)



#include <stdlib.h>
#define HIMFRAG_SRC_T void *
#define HIMFRAG_SRC_VERIFY(src) (src != NULL)


struct hiena_mfrag {
        struct hiena_svc *svc;
        void *addr;
        HIMFRAG_BOUND_T boundhead;
        HIMFRAG_BOUND_T boundtail;
        void *buf;
        HIMFRAG_BUFSIZE_T bufsize;
        HIMFRAG_BOUND_T bufh;
        HIMFRAG_BOUND_T buft;
        int flags;
};

struct hiena_mfrag *mfrag_new();
struct hiena_mfrag *mfrag_dup( struct hiena_mfrag * );

void mfrag_cleanup( struct hiena_mfrag *mf );

int mfrag_set_svc( struct hiena_mfrag *f, struct hiena_svc *svc );

int mfrag_set_addr( struct hiena_mfrag *mf, void *addr );

int mfrag_set_bounds( struct hiena_mfrag *mf, HIMFRAG_BOUND_T bh, HIMFRAG_BOUND_T bt );

int mfrag_set_boundhead( struct hiena_mfrag *mf, HIMFRAG_BOUND_T );

int mfrag_set_boundtail( struct hiena_mfrag *mf, HIMFRAG_BOUND_T );

HIMFRAG_BOUND_T mfrag_get_length( struct hiena_mfrag *mf );





#endif /* ! HIENA_MFRAG_H */
