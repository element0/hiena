





#include <stdio.h>
#include <sys/stat.h>
#include "../frag.h"
#include "../mfrag.h"
#include "../hiena_fh.h"
#include "../frag_fh.h"
#include "../file_svc.h"
#include "../mfrag_svc.h"



static void print_usage ( char *s )
{
        printf("%s SRCFILE STARTBYTE ENDBYTE DSTFILE AT_BYTE\n", s );
        printf("example: %s insertthis.txt 100 300 intothisat.txt 15", s );
}


static off_t get_filesize( char *n )
{
        struct stat sb;
        stat( n, &sb );
        return sb.st_size;
}



int main( int argc, char *argv[] )
{
        if( argc != 6 )
        {
                print_usage( argv[0] );
                return -1;
        }

        struct hiena_frag *f, *f2;
        struct hiena_mfrag *dstmf;
        struct hiena_mfrag *srcmf;
        void *dsta, *srca;
        struct hiena_svc *filesvc;

        char c;

        f = new_frag( );
        f2 = new_frag( );

        dstmf = new_mfrag( );
        srcmf = new_mfrag( );

        filesvc = &file_svc_ops;

        srca = argv[1];
        dsta = argv[4];

        mfrag_set_addr( srcmf, srca );
        mfrag_set_addr( dstmf, dsta );

        mfrag_set_svc( srcmf, filesvc );
        mfrag_set_svc( dstmf, filesvc );


        mfrag_set_bounds( srcmf, atoi( argv[2] ),
                atoi( argv[3] ) );
        mfrag_set_bounds( dstmf, 0,
                get_filesize( argv[4] ) );

        frag_set_mfrag( f, dstmf );
        frag_set_mfrag( f2, srcmf );

        frag_insert( f, f2, atoi( argv[5] ));

        /*
        struct hiena_fh *fh;
        fh = frag_fh_open( f );

        while(( c = fh->ops->getc( fh )) != EOF )
                  //---------------------

        {
                fputc( c, stdout );
        }
        fputc('\n', stdout);

        frag_fh_close( fh );
        */

        mfrag_cleanup( srcmf );
        mfrag_cleanup( dstmf );
        frag_cleanup( f );
        frag_cleanup( f2 );

        return 0;
}
