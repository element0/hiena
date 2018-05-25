
#include <stdio.h>
#include "dcel.h"
#include "dcel_dirent.h"
#include "cosmos.h"
#include "hierr.h"
#include "lookup_hdl.h"
#include "lookup_svc.h"
#include "access_frame.h"



int main()
{

        struct hiena_dcel *dc, *dc2, *dc3, *dc4;
        struct access_frame *af, *af2, *af3, *af4;
        lookup_target_t *res;
        struct dcel_dirent *e;
        struct cosmos *cm;
        struct lookup_hdl *h;
        
        dc = dcel_new(NULL);
        if( dc == NULL )
        {
                HIERR("test_lookup_svc::main: err: dc NULL");
                return -1;
        }
        
        
        
        /* init cosmos_db */

        cm = cosmos_db_new();


        /* init dcel's */

        dc2 = dcel_new(dc);
        dc3 = dcel_new(dc2);
        dc4 = dcel_new(dc3);

        /* dcel_add_child seg-faults if arg 3 NULL */

        dcel_add_child( dc, "wings", dc2, cm );
        dcel_add_child( dc, "beak", dc3, cm );
        dcel_add_child( dc, "down", dc4, cm );


        /* init access frames */
        
        af = aframe_new();
        af->dcel = dc;

        /* init lookup hdl */

        h = lookup_hdl_new();
        h->cosmos = cm;
        h->target = (cosmos_id_t)af;
        h->find_child = lookup_find_child;




        /* lookup svc test: find child */

        res = h->find_child( h, "wings" );



        if( res == NULL )
        {
                HIERR("test_lookup_svc::main: err: res NULL");
        }



        dcel_cleanup(dc2);
        cosmos_db_cleanup(cm);

        return 0;
}
