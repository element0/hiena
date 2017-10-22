

#include <stdio.h>
#include "lookup_module.h"
#include "lookup\ module/fudge/fudge.h"


int main( int argc, char *argv[] )
{
        if( argc != 5 )
        {
                printf("usage: %s SCANNERLIBDIR LOOKUPMODPATH FILEPATH LOOKUPSTRING\n", argv[0]);
                return -1;
        }

        char *ln, *lu, *fn, *ls;

        struct hiena_dcel *dc;

        struct hiena_slib *slib;
        struct hiena_scanner *hs;

        struct lookup_hdl *h;

        ln = argv[1];
        lu = argv[2];
        fn = argv[3];
        ls = argv[3];

        dc = dsource(NULL, 1, (void **)&fn);

        slib = slib_load_dir( ln, NULL );

        h = lookup_module_init( dc, slib );

        h->lookup_str = ls;

        fudge_parse( h );

        dcel_cleanup( dc );
        slib_cleanup( slib );

        return 0;
}