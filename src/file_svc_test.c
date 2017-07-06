#include <stdio.h>
#include <errno.h>
#include "file_svc.h"


int main( int argc, char *argv[] )
{
        if( argv == NULL )
        {
                fprintf(stderr, "test_file_svc function was called with a null argv.\n");
                return -1;
        }

        if( argc != 2 )
        {
                fprintf(stderr, "usage: %s FILENAME\n", argv[0]);
                return -1;
        }


        char *addr;
        struct hiena_svc *svc;
        void *h;

        char c;
        char buf[32];
        size_t nread;
        int er;
        int erno;
        int ret;

        addr = argv[1];
        svc = &file_svc_ops;
        h = svc->open( addr, "r" );

        if( h == NULL )
        {
                fprintf(stderr, "file_svc_test: err: open( %s, \"r\" ) returned null.\n", addr );
                return -1;
        }

        while(( c = svc->getchar( h ), c) != EOF )
        {
                fputc(c, stdout);
        }
        fputc('\n',stdout);

        if( c == EOF )
        {
                fprintf(stderr, "file_svc_test: EOF: getc() from %s\n", addr );
        }

        

        er = svc->close( h );
        erno = errno;

        if( er == EOF )
        {
                fprintf(stderr, "file_svc_test: EOF, errno %d: close() on %s\n", erno, addr );
                return -1;
        }

        return 0;
}
