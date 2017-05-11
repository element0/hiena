




#ifndef HIENA_SERVICE_FRAG_H
#define HIENA_SERVICE_FRAG_H

#include "frag.h"

#undef MYSVC_ADDR_INIT_PARMS
#define MYSVC_ADDR_INIT_PARMS struct hiena_frag *

#include "hiena_svc.h"
#include "frag_fh.h"


struct hiena_svc *frag_svc_new();
int frag_svc_cleanup( struct hiena_svc * );

#endif /*! HIENA_SERVICE_FRAG_H */
