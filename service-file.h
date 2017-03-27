




#ifndef HIENA_SERVICE_FILE_H
#define HIENA_SERVICE_FILE_H

#define MYSVC_ADDR_INIT_PARMS char *pathname

#include "service.h"

struct hiena_svc_module *service_file_new();

struct hiena_svc_addr *service_file_addr_new( MYSVC_ADDR_INIT_PARMS );

void service_file_addr_cleanup( struct hiena_svc_addr  *hsa );

#endif /*! HIENA_SERVICE_FILE_H */
