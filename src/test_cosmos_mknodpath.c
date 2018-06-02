#include "cosmos.h"




int main( int argc, char *argv[] )
{
        struct cosmos *cm;
        cosmos_id_t cur, proto;
        char *pathname;

        cm = cosmos_init();

        protoframe = cm->proto; 

        pathname = cosmos_calc_fnpath(cm, "lookup", "cosmos_lookup_fn");

        cur = cosmos_mknod_path(cm, protoframe, 


        cosmos_db_cleanup(cm);

        return 0;
}
