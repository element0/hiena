#ifndef HIENA_DCEL_SVC_H
#define HIENA_DCEL_SVC_H

#include "hiena_svc.h"










void *dcel_svc_open( void *, const char * );

int dcel_svc_close( void * );

int dcel_svc_getc( void *fh );



struct hiena_svc dcel_svc_ops;


#endif /* ! HIENA_DCEL_SVC_H */