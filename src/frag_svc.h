




#ifndef HIENA_SERVICE_FRAG_H
#define HIENA_SERVICE_FRAG_H

#include "hiena_svc.h"
#include "frag.h"
#include "frag_fh.h"


struct hiena_svc *frag_svc_new();

int frag_svc_cleanup( struct hiena_svc * );

size_t frag_svc_read( void *buf, size_t len, size_t n, void *fh );

size_t frag_svc_write( void *tbd, size_t tbd2, size_t tbd3, void *fh );

void *frag_svc_open( void *, const char * );

int frag_svc_close( void * );

int frag_svc_seek( void *fh, long len, int w);

int frag_svc_getc( void *fh );


struct hiena_svc frag_svc_ops;


#endif /*! HIENA_SERVICE_FRAG_H */
