#include <stdlib.h>
#include "dcel.h"
#include "access_frame.h"
#include "prod_instr.h"


struct hiena_dcel *prod_exec( struct prod_instr *pi )
{
        if( pi == NULL )
        {
                HIERR("prod_instr: err: pi NULL");
                return NULL;
        }

        struct hiena_dcel *dc;
        struct hiena_dcel *(*fn)
        (
            struct context_frame *,
            int argc,
            void **argv
        );

        struct context_frame *cx;
        int argc;
        void **argv;

        fn = pi->prod_fn;
        cx = pi->context_frame;
        argc = pi->argc;
        argv = pi->argv;

        if( fn == NULL )
        {
                HIERR("prod_exec: err: fn NULL");
                return NULL;
        }

        dc = fn(cx, argc, argv);

        return dc;
}