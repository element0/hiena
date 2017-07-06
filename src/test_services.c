

#include <stdio.h>
#include <errno.h>
#include "file_svc.h"
#include "mfrag.h"
#include "mfrag_svc.h"


int main( int argc, char *argv[] )
{
        if( argv == NULL )
        {
                fprintf(stderr, "test_services function was called with a null argv.\n");
                return -1;
        }

        if( argc != 2 )
        {
                fprintf(stderr, "usage: %s FILENAME\n", argv[0]);
                return -1;
        }

        const int nsvc = 2;
        int i = 0;

        void *addr[nsvc];
        struct hiena_svc *svc[nsvc];
        void *fh;

        struct hiena_mfrag *mfrag;

        char c;
        char buf[32];
        size_t nread;
        int er;
        int erno;
        int ret;

        /* init file svc */

        addr[i] = (void *)argv[1];
        svc[i] = &file_svc_ops;
        i++;

        /* init mfrag svc */

        mfrag = mfrag_new();
        mfrag->addr = (void *)argv[1];
        mfrag->svc = &file_svc_ops;
        mfrag->boundhead = 3;
        mfrag->boundtail = 8;

        addr[i] = (void *)mfrag;
        svc[i] = &mfrag_svc_ops;
        i++;


        /* test loop */

        for(i=0;i<nsvc;i++)
        {

                fh = svc[i]->open( addr[i], "r" );   

                if( fh == NULL )
                {
                        fprintf (stderr, "test_services: err: open( addr[%d], \"r\" ) returned null.\n", i );
                        return -1;
                }

                while(( c = svc[i]->getchar( fh ), c) != EOF )
                {
                        fputc(c, stdout);
                }
                fputc('\n',stdout);

                if( c == EOF )
                {
                        fprintf ( stderr, "test_services: EOF: getc() from addr[%d]\n", i );
                }

                er = svc[i]->close( fh );
                erno = errno;

                if( er == EOF )
                {
                        fprintf ( stderr, "test_services: EOF, errno %d: close() on addr[%d]\n", erno, i );
                        return -1;
                }

        }
        return 0;
}
