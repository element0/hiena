

#include <stdio.h>
#include "dcel.h"
#include "dcel_dirent.h"
#include "cosmos.h"
#include "hierr.h"

int main()
{

        struct hiena_dcel *dc, *dc2, *dc3, *dc4;
        struct hiena_dcel *res;
        struct dcel_dirent *e;
        struct cosmos *cm;
        
        dc = dcel_new(NULL);
        if( dc == NULL )
        {
                HIERR("test_dcel_child::main: err: dc NULL");
                return -1;
        }

        dc2 = dcel_new(dc);
        dc3 = dcel_new(dc2);
        dc4 = dcel_new(dc3);
        cm = cosmos_db_new();


        /* dcel_add_child seg-faults if arg 3 NULL */

        dcel_add_child( dc, "wings", dc2, cm );
        dcel_add_child( dc, "beak", dc3, cm );
        dcel_add_child( dc, "down", dc4, cm );

        res = dcel_find_child( dc, "wings", cm );


        /* note:
           result is not the same dcel as dc2.
           result is a container for the find results list.

           res->child_list->dcel should equal dc2.
         */


        if( res == NULL )
        {
                HIERR("test_dcel_child::main: err: res NULL");

        }

        e = res->child_list;

        if( e == NULL )
        {
                HIERR("test_dcel_child::main: err: res->child_list NULL");
        }

        if( e->dcel != dc2 )
        {
               HIERR("test_dcel_child::main: err: res->child_list != dc2");

        }
        
        else{
               printf("SUCCESS! res->child_list == dc2\n");
        }


        /* lookup another child */

        res = dcel_find_child( dc, "down", cm );
        if( res == NULL )
        {
                HIERR("test_dcel_child::main: err: res NULL");

        }

        e = res->child_list;

        if( e == NULL )
        {
                HIERR("test_dcel_child::main: err: res->child_list NULL");
        }

        if( e->dcel != dc2 )
        {
               HIERR("test_dcel_child::main: err: res->child_list != dc2");

        }
        
        else{
               printf("SUCCESS! found \"down\"\n");
        }



        /* list children */

        for(e = dc->child_list; e != NULL; e = e->next)
        {
                if( e->d_name != NULL )
                        printf("%s\n", e->d_name);
                else
                        printf("d_name: NULL\n");
        }

        dcel_cleanup(dc2);
        cosmos_db_cleanup(cm);

        return 0;
}
