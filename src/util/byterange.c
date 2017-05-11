#include <stdio.h>

/*
  uses hiena service modules
 */

#include "../hiena_svc.h"
#include "../file_svc.h"


int main( int argc, char *argv[] )
{
        struct hiena_svc *hsm;
        void *fp, *ptr;
        long len;
        char *s;

        if( argc != 4 )
                return -1;

        hsm = &file_svc_ops;
        len = atoi(argv[3]) + 1;
        ptr = malloc(sizeof(char)*len);

        fp = hsm->open( argv[1], "r" );
        hsm->seek( fp, atoi(argv[2]), SEEK_SET ); 
        hsm->read( ptr, atoi(argv[3]), 1, fp );
        hsm->close( fp );

        s = ptr;
        s[ len -1 ] = '\0';
        printf("%s", s);

        free(ptr);

        return 0;
}
