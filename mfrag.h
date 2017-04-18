





#ifndef HIENA_MFRAG_H
#define HIENA_MFRAG_H

#include <sys/types.h>
#define HIMFRAG_BOUND_T off_t
#define HIMFRAG_BOUNDS_MIN 0
#define HIMFRAG_BOUNDS_MAX (2^31)

#define HIMFRAG_BUFSIZE_T size_t
/* 20170324 pos and off should match */
#define HIMFRAG_POS_T off_t
#define HIMFRAG_OFF_T off_t
#define HIMFRAG_OFF_MIN 0
#define HIMFRAG_OFF_MAX (2^31)



#include <stdlib.h>
#define HIMFRAG_SRC_T void *
#define HIMFRAG_SRC_VERIFY(src) (src != NULL)

#define HIMFRAG_SRC_IO_T struct hiena_src_io *

#define HIMFRAG_IO_VERIFY(mfio) (mfio != NULL)

struct hiena_mfrag {
        HIMFRAG_SRC_T   src;
        HIMFRAG_BOUND_T boundhead;
        HIMFRAG_BOUND_T boundtail;
        void *buf;
        HIMFRAG_BUFSIZE_T bufsize;
        HIMFRAG_BOUND_T bufh;
        HIMFRAG_BOUND_T buft;
        int flags;
};

struct hiena_mfrag *new_mfrag();

void mfrag_cleanup( struct hiena_mfrag *mf );

int mfrag_set_src( struct hiena_mfrag *mf, HIMFRAG_SRC_T src );

int mfrag_set_bounds( struct hiena_mfrag *mf, HIMFRAG_BOUND_T bh, HIMFRAG_BOUND_T bt );

int mfrag_set_boundhead( struct hiena_mfrag *mf, HIMFRAG_BOUND_T );

int mfrag_set_boundtail( struct hiena_mfrag *mf, HIMFRAG_BOUND_T );

struct hiena_mfrag_io {
        struct hiena_mfrag *mf;
        HIMFRAG_POS_T pos;
        HIMFRAG_SRC_IO_T sio;
};

int mfrag_io_seek( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off );

HIMFRAG_BUFSIZE_T mfrag_io_read( struct hiena_mfrag_io *mfio, void *dst, HIMFRAG_BUFSIZE_T size );

HIMFRAG_BUFSIZE_T mfrag_io_write( struct hiena_mfrag_io *mfio, HIMFRAG_BUFSIZE_T size );

HIMFRAG_BUFSIZE_T mfrag_io_append( struct hiena_mfrag_io *mfio, void *buf, HIMFRAG_BUFSIZE_T len );

HIMFRAG_BUFSIZE_T mfrag_io_overwrite( struct hiena_mfrag_io *mfio, void *buf, HIMFRAG_BUFSIZE_T len );

HIMFRAG_OFF_T mfrag_io_trim_tail( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off );

HIMFRAG_OFF_T mfrag_io_trim_head( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off );

int mfrag_io_flush( struct hiena_mfrag_io *mfio );



#endif /* ! HIENA_MFRAG_H */
