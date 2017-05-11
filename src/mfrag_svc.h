




#ifndef HIENA_MFRAG_SVC_H
#define HIENA_MFRAG_SVC_H

#include "mfrag.h"
#include "hiena_svc.h"
#include "mfrag_fh.h"

#define HIMFRAG_IO_VERIFY(mfio) (mfio != NULL)


struct hiena_svc *mfrag_svc_new();

int mfrag_svc_cleanup( struct hiena_svc * );


int mfrag_fh_seek( struct hiena_fh *, off_t off );

size_t mfrag_fh_read( struct hiena_fh *, void *dst, size_t size );

size_t mfrag_fh_write( struct hiena_fh *, size_t

size_t mfrag_fh_append( struct hiena_fh *, void *buf, size_t len );

size_t mfrag_fh_overwrite( struct hiena_fh *, void *buf, size_t len );

off_t mfrag_fh_trim_tail( struct hiena_fh *, off_t off );

off_t mfrag_fh_trim_head( struct hiena_fh *, off_t off );

int mfrag_fh_flush( struct hiena_fh * );


#endif /*! HIENA_MFRAG_SVC_H */
