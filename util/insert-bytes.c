





#include <stdio.h>
#include "../frag.h"
#include "../service-file.h"



static void print_usage ( char *s )
{
        printf("%s SRCFILE STARTBYTE ENDBYTE DSTFILE AT_BYTE" );
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
                print_usage(vargc[0] );
                return -1;
        }

        struct hiena_svc_module *filesvc;
        struct hiena_svc_addr *srca;
        struct hiena_svc_addr *dsta;

        struct hiena_frag *f;
        struct hiena_mfrag *srcmf;
        struct hiena_mfrag *dstmf;

        filesvc = service_file_new( );

        srca = service_file_addr_new( argv[1] );
        service_addr_set_svc( srca, filesvc );

        dsta = service_file_addr_new( argv[1] );
        service_addr_set_svc( dsta, filesvc );

        frag_set_media( f, srcmf );

        mfrag_set_src( srcmf, src );
        mfrag_set_bounds( srcmf, atoi( argv[2] ), atoi( argv[3] ) );

        mfrag_set_src( dstmf, dst );
        mfrag_set_bounds( dstmf, 0, get_filesize( argv[4] ) );

        return 0;
}