#include <stdio.h>
#include "../hierr.h"
#include "cosmos_db.h"
#include "cosmos_init.h"



int main(int argc, char *argv[])
{
        struct cosmos *cm;
        int er;



        cm = cosmos_init(0, NULL);
        if(cm == NULL)
        {
HIERR("cosmos_init_test:: err: fail to init cosmos db");
                return -1;
        }


        er = cosmos_db_cleanup(cm);
        if(er != 0)
        {
                HIERR("cosmos_init_test: cosmos_db_cleanup: return non zero");
                return -1;
        }


        return 0;
}