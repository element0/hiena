#include <stdio.h>

/*
  uses hiena service modules
 */

#include "../service.h"
#include "../service-file.h"


int main( int argc, char *argv[] )
{

        struct hiena_svc_module *hsm = service_file_new( );
       
        struct hiena_svc_addr *addr = NULL;

        void *fp  = NULL;
        void *ptr = NULL;
        long len  = 0;

        if( argc == 4 )
	     {
                addr = service_file_addr_new( argv[2] );

                len = atoi(argv[3]) + 1;

		ptr = malloc(sizeof(char)*len);
		fp = hsm->open( argv[1], "r" );

		hsm->seek( fp, atoi(argv[2]), SEEK_SET ); 
		hsm->read( ptr, atoi(argv[3]), 1, fp );
		hsm->close( fp );


		char *s = ptr;
		s[ len -1 ] = '\0';

		printf("%s", s);

		free(ptr);
	        service_file_addr_cleanup( addr );
	}

	hiena_svc_module_cleanup( hsm );

	return 0;
}
