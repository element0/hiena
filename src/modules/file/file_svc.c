#include <stdio.h>
#include <sys/stat.h>
#include "../../hiena_svc.h"

off_t get_filesize( char *n )
{
        struct stat sb;
        stat( n, &sb );
        return sb.st_size;
}


/* WIP
   adding a get_size() op.
   adding directory ops.
*/


struct hiena_svc file_svc_ops = {
        .read = (size_t (*)( void *, size_t, size_t, void *))fread,
        .write = (size_t (*)( void *, size_t, size_t, void *))fwrite,
        .open  = (void *(*)( void *, const char *))fopen,
        .close = (int (*)( void * ))fclose,
        .seek  = (int (*)( void *, long, int ))fseek,
        .getchar  = (int (*)( void * ))fgetc,
        .get_size = get_filesize,
        .opendir = (void *(*)(void *))opendir,
        .readdir = (void *(*)(void *),
        .closedir = (void *(*)(void *),

};
