
#include <stdio.h>
#include "cosmos_db.h"
#include "cosmos_module.h"
#include "cosmos_config.h"
#include "../hierr.h"


int main(int argc, char *argv[])
{
        struct cosmos *cm;
        char *fnpath;

        cm = cosmos_db_new();

        if(cosmos_config(cm) == -1)
        {
HIERR("test_cosmos_module::main: err: fail to configure cosmos db");
                return -1;
        }

        fnpath = cosmos_calc_fnpath(cm, "file", "cosmos_map_fn");

        printf("test_cosmos_module::main: success: fnpath == %s\n", fnpath);

        return 0;
}