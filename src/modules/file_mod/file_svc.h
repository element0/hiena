




#ifndef HIENA_FILE_SVC_H
#define HIENA_FILE_SVC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../hiena_svc.h"

struct hiena_svc file_svc_ops;

off_t get_filesize( char * );

#endif /*! HIENA_FILE_SVC_H */
