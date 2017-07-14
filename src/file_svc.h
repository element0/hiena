




#ifndef HIENA_FILE_SVC_H
#define HIENA_FILE_SVC_H

#include "hiena_svc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hiena_svc file_svc_ops = {
        .read = (size_t (*)( void *, size_t, size_t, void *))fread,
        .write = (size_t (*)( void *, size_t, size_t, void *))fwrite,
        .open  = (void * (*)( void *, const char *))fopen,
        .close = (int    (*)( void * ))fclose,
        .seek  = (int    (*)( void *, long, int ))fseek,
        .getchar  = (int    (*)( void * ))fgetc,
};

off_t get_filesize( char * );

#endif /*! HIENA_FILE_SVC_H */
