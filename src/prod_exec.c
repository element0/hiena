#include <stdlib.h>
#include "dcel.h"
#include "access_frame.h"
#include "prod_instr.h"
#include "cosmos/cosmos_db.h"
#include "cosmos/cosmos_fs.h"



struct hiena_dcel *prod_exec( struct cosmos *cm, struct prod_instr *pi )
{
        if( pi == NULL )
        {
                HIERR("prod_instr: err: pi NULL");
                return NULL;
        }


        struct access_frame *func;
        struct access_frame *af;
        int argc;
        void **argv;
        struct access_frame *res;
        struct hiena_dcel *dc;


        func = pi->fn;
        fn = pi->fnptr;
        af = pi->access_frame;
        argc = pi->argc;
        argv = pi->argv;


        if( fn == NULL )
        {

                HIERR("prod_exec: err: fn NULL");

                return NULL;
        }


        res = cosmos_exec(cm, af, func, argc, argv);

        dc = res->dc;

        if( dc == NULL )
        {

                HIERR("prod_exec: err: couldn't generate dcel");

                return NULL;
        }

        /* uncomment if you don't
           want to cache result */
        /*
        cosmos_unlink(res);
        */

        dcel_retain(dc);
        dc->prod_instr = pi;

        return dc;
}