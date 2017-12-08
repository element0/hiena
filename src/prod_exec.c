#include <stdlib.h>
#include "dcel.h"
#include "access_frame.h"
#include "prod_instr.h"
#include "cosmos/cosmos_obj.h"


struct hiena_dcel *prod_exec( struct prod_instr *pi )
{
        if( pi == NULL )
        {
                HIERR("prod_instr: err: pi NULL");
                return NULL;
        }

        struct hiena_dcel *dc;
        prodfn_guid_t *fnid;
        PRODFN_T(fn);

        struct cosmos *cm;
        struct context_frame *cx;
        int argc;
        void **argv;

        fnid = pi->prodfn_guid;
        fn = pi->prod_fn;
        cx = pi->context_frame;
        argc = pi->argc;
        argv = pi->argv;

        cm = cx->cosmos_obj;

        if( fn == NULL )
        {
                fn = cosmos_prodfn_get(cm, prodfn_guid);
        }

        if( fn == NULL )
        {

                HIERR("prod_exec: err: fn NULL");

                return NULL;
        }

        dc = fn(cx, argc, argv);

        return dc;
}