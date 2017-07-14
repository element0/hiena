





#include <stdio.h>

#include "../hiena_fh.h"
#include "../hiena_svc.h"
#include "../file_svc.h"
#include "../mfrag.h"
#include "../mfrag_fh.h"
#include "../mfrag_svc.h"
#include "../frag.h"
#include "../frag_fh.h"
#include "../frag_svc.h"


static void print_usage ( char *s )
{
        printf("%s SRCFILE STARTBYTE ENDBYTE DSTFILE AT_BYTE\n", s );
        printf("example: %s insertthis.txt 100 300 intothisat.txt 15", s );
}



struct hiena_frag *insert_bytes_util( int argc, char *argv[] )
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

        f = new_frag( );
        f2 = new_frag( );

        dstmf = mfrag_new( );
        srcmf = mfrag_new( );

        srca = (void *)argv[1];
        dsta = (void *)argv[4];

        mfrag_set_addr( srcmf, srca );
        mfrag_set_addr( dstmf, dsta );

        mfrag_set_svc( srcmf, filesvc );
        mfrag_set_svc( dstmf, filesvc );


        mfrag_set_bounds( srcmf, atoi( argv[2] ),
                atoi( argv[2] ) + atoi( argv[3] ) );
        mfrag_set_bounds( dstmf, 0,
                get_filesize( argv[4] ) );

        frag_set_mfrag( f, dstmf );
        frag_set_mfrag( f2, srcmf );

        frag_insert( f, f2, atoi( argv[5] ));

        frag_cleanup( f2 );

        return f;
}


void frag_print( struct hiena_frag *f )
{
        void *fh;
        char c;

        fh = frag_svc_open( f, "r" );


        while(( c = frag_svc_ops.getchar(fh)) != EOF )
        {
                fputc( c, stdout );
        }
        fputc('\n', stdout);

        frag_svc_close( fh );
}

int insert_bytes_cleanup( struct hiena_frag *f )
}
        /*
        mfrag_cleanup( srcmf );
        mfrag_cleanup( dstmf );
        frag_cleanup( f );
        */

        return 0;
}
