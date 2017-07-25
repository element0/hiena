









#include <stdlib.h>
#include <dirent.h>
#include "../slib.h"
#include "../scanner.h"
#include "../scanner_hdl.h"
#include "../dcel.h"
#include "../dcel_fh.h"
#include "../dcel_dirsvc.h"
#include "../dsource.h"
#include "../hierr.h"


static util_print_dir( struct hiena_dcel *dc )
{
	struct dcel_fh *d;
	struct dirent *e;

        d = dcel_dirsvc.opendir(dc);
        if(d == NULL)
        {
                HIERR("hiena_ls_util/util_print_dir: d NULL.");
                return -1;
        }

        while(( e = dcel_dirsvc.readdir(d) ) != NULL )
        {
                printf("%s\n", e->d_name);
        }

        dcel_dirsvc.closedir(d);

        return 0;
}



int main( int argc, char *argv[] )
{
        if( argc < 4 )
        {
                printf("usage: %s SCANNERLIBDIR SCANNERNAME FILE\n", argv[0]);
                return -1;
        }

        char *hp, *sn, *fn;
        struct hiena_slib *slib;
        struct hiena_scanner *hs;
        struct hiena_dcel *dc;
        struct scanner_hdl *hsp;

        hp = argv[1];
        sn = argv[2];
        fn = argv[3];

        slib = slib_load_dir( hp, NULL );

        hs = slib_get_scanner(sn,slib);


        dc = dsource(NULL, 1, (void **)&fn);


        hsp = hsp_init_src_scanner_slib( dc, hs, slib );



        hs->op->parse( hsp );
        //--------

/*
        util_print_dir( dc );
*/
        hsp_cleanup( hsp );
        dcel_cleanup( dc );
        slib_cleanup( slib );

        return 0;
}
