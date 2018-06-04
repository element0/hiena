#include <stdlib.h>
#include "cosmos.h"




int main( int argc, char *argv[] )
{
        struct cosmos *cm;
        cosmos_id_t cur, protoframe, root, res;
        char *pathname;

        cm = cosmos_init(argc, argv);

        protoframe = cm->proto;
        root = cm->root;


        /* test mknod_path */

        pathname = cosmos_calc_fnpath(cm, "lookup", "cosmos_lookup_fn");

        cur = cosmos_mknod_path(cm, root, pathname, 0, 0); 

        res = cosmos_lookup(cm, root, pathname);

        printf("test_cosmos_mknodpath: res %lu\n", (unsigned long)res);

        free(pathname);




        /* WIP: mknod, bind, lookup */

        printf("\ntesting mknod, bind, lookup sequence...\n\n");

        pathname = "bear/koala";
        
        cur = cosmos_mknod_path(cm, root, pathname, 0, 0); 

        cosmos_bind(cm, cur, "file", "../", COSMOS_ID_NULL);

        res = cosmos_lookup(cm, root, pathname);

        printf("test_cosmos_mknodpath: res %lu\n", (unsigned long)res);


        if(argc > 1)
        {
                pathname = argv[1];

                res = cosmos_lookup(cm, res, pathname);
        }




        /* cleanup */

        cosmos_db_cleanup(cm);

        return 0;
}
