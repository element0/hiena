#ifndef HIENA_SERVICE_H
#define HIENA_SERVICE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct hiena_svc
{
        void *(*source)( void *addr, void *cosmos_db );
        void *(*map)( void *target, void *cosmos_db );
        void *(*transform)( void *target, void *cosmos_db );

        void * (*open)( void *addr, const char *mode);
        int    (*close)( void *fp );
        int    (*seek)( void *fp, long offset, int whence );
        size_t (*read)( void *ptr, size_t size, size_t nmemb, void *fp );
        size_t (*write)( void *ptr, size_t size, size_t nmemb, void *fp );
        int (*getchar)( void *fp );
        void *(*opendir)(void *addr);
        void *(*readdir)(void *dir);
        int (*closedir)(void *dir);
        int (*mknod)(void *dir, char *dname, void *mode);

        int (*stat)(void *cm, uintptr_t *id, void *addr, void *sb);

        off_t (*get_size)( char *n );

};



#endif /*!HIENA_SERVICE_H*/
