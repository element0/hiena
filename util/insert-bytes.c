





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

        struct hiena_frag *f;
        struct hiena_mfrag *dstmf;
        struct hiena_svc_addr *dsta;
        struct hiena_svc_module *filesvc;

        struct hiena_mfrag *srcmf;
        struct hiena_svc_addr *srca;

	f = new_frag( );

	dstmf = new_mfrag( );
	srcmf = new_mfrag( );

        filesvc = service_file_new( );

        srca = service_file_addr_new( argv[1] );
        dsta = service_file_addr_new( argv[1] );

        mfrag_set_addr( srcmf, srca );
	mfrag_set_addr( dstmf, dsta );

	mfrag_set_svc( srcmf, filesvc );
	mfrag_set_svc( dstmf, filesvc );

        frag_set_media( f, dstmf );

        mfrag_set_bounds( srcmf, atoi( argv[2] ), atoi( argv[3] ) );
        mfrag_set_bounds( dstmf, 0, get_filesize( argv[4] ) );

	service_file_addr_cleanup( srca );
	service_file_addr_cleanup( dsta );
	service_file_cleanup( filesvc );

	mfrag_cleanup( srcmf );
	mfrag_cleanup( dstmf );
	frag_cleanup( f );

        return 0;
}
