
#include <stdio.h>
#include "cosmos_db.h"
#include "cosmos_module.h"
#include "cosmos_config.h"
#include "cosmos_load_module.h"
#include "../hierr.h"


int main(int argc, char *argv[])
{
        struct cosmos *cm;
        char *fnpath;
        cosmos_module_t *lookmod;

        cm = cosmos_db_new();

        if(cosmos_config(cm) == -1)
        {
HIERR("test_cosmos_module::main: err: fail to configure cosmos db");
                return -1;
        }


        /*
         * load lookup module
         */

        lookmod = cosmos_load_mod(cm, cm->host_lookupmod_fpath);

        
        cosmos_db_cleanup(cm);

        return 0;
}