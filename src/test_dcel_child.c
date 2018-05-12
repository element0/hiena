

#include <stdio.h>
#include "dcel.h"
#include "cosmos.h"
#include "hierr.h"

int main()
{

        struct hiena_dcel *dc, *dc2;
        struct hiena_dcel *res;
        struct cosmos *cm;
        
        dc = dcel_new(NULL);
        if( dc == NULL )
        {
                HIERR("test_dcel_child::main: err: dc NULL");
                return -1;
        }

        dc2 = dcel_new(dc);
        cm = cosmos_db_new();

        dcel_add_child( dc, "wings", dc2, cm );

        res = dcel_find_child( dc, "wings", cm );

        if( res == NULL )
        {
                HIERR("test_dcel_child::main: err: res NULL");

        }

        if( res != dc2 )
        {
               HIERR("test_dcel_child::main: err: res != dc2");

        }


        dcel_cleanup(dc2);
        cosmos_db_cleanup(cm);

        return 0;
}