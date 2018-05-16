#include <stdlib.h>
#include "dcel.h"
#include "access_frame.h"
#include "cosmos.h"
#include "hierr.h"


/*
    convenience function.  avoids prod instr syntax in the API and hides it during development.

 */
cosmos_id_t prod_find_child(cosmos_id_t par, char *name, struct cosmos *cm)
{
        (struct access_frame *)par;
        struct hiena_dcel *dc, *dc2;
        struct access_frame *af;



        if(par == COSMOS_ID_NULL)
        {
                HIERR("prod_find_child: err: par NULL");
                return COSMOS_ID_NULL;
        }

        if(cm == COSMOS_ID_NULL)
        {
                HIERR("prod_find_child: err: cm NULL");
                return COSMOS_ID_NULL;
        }




        dc = par->dcel;
        dc2 = dcel_find_child(dc, name, cm);
        af = aframe_new();
        af->dcel = dc2;
     
        return (cosmos_id_t)af;
}

