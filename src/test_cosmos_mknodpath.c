#include <stdlib.h>
#include "cosmos.h"




int main( int argc, char *argv[] )
{
        struct cosmos *cm;
        cosmos_id_t cur, protoframe;
        char *pathname;

        cm = cosmos_init(argc, *argv);

        protoframe = cm->proto; 

        pathname = cosmos_calc_fnpath(cm, "lookup", "cosmos_lookup_fn");

        cur = cosmos_mknod_path(cm, protoframe, pathname, 0, 0); 

        free(pathname);

        cosmos_db_cleanup(cm);

        return 0;
}
