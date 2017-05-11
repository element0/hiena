




#ifndef HIENA_MFRAG_SVC_H
#define HIENA_MFRAG_SVC_H

#include "mfrag.h"
#include "hiena_svc.h"
#include "mfrag_fh.h"


struct hiena_svc *mfrag_svc_new();

int mfrag_svc_cleanup( struct hiena_svc * );

#endif /*! HIENA_MFRAG_SVC_H */
