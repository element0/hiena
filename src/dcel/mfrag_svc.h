




#ifndef HIENA_MFRAG_SVC_H
#define HIENA_MFRAG_SVC_H

#include "hiena_fh.h"
#include "hiena_svc.h"
#include "mfrag.h"
#include "mfrag_fh.h"

#define HIMFRAG_IO_VERIFY(mfio) (mfio != NULL)


struct hiena_svc *mfrag_svc_new();

int mfrag_svc_cleanup( struct hiena_svc * );


size_t mfrag_svc_read( void *, size_t, size_t, void * );

size_t mfrag_svc_write( void *, size_t, size_t, void * );

void *mfrag_svc_open( void *mfa, const char *mode );

int mfrag_svc_close( void *fh );

int mfrag_svc_seek( void *, long, int );

int mfrag_svc_getc( void *fh );


int mfrag_svc_flush( void * );


struct hiena_svc mfrag_svc_ops;


size_t mfrag_svc_append( struct mfrag_fh *, void *buf, size_t len );

size_t mfrag_svc_overwrite( struct mfrag_fh *, void *buf, size_t len );

off_t mfrag_svc_trim_tail( struct mfrag_fh *, off_t off );

off_t mfrag_svc_trim_head( struct mfrag_fh *, off_t off );


#endif /*! HIENA_MFRAG_SVC_H */
