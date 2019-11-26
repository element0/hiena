#ifndef HIENA_PRODUCER_ARGS_H
#define HIENA_PRODUCER_ARGS_H

/** @file prod_args.h
 *
 * Production instruction args.
 * An array for tracking arguments which will be passed to
 * a producer module. The module might be a function or
 * might be an external process launched through a shell.
 *
 * Producer Args need to contain enough info to be serialzed.
 *
 * Maybe replace with flatbuffers?
 */
#include <sys/types.h>
#include "cosmos.h"

enum pi_arg_types {
        PI_INT,
        PI_STR,
        PI_STR_ID,
        PI_COSMOS_ID
};



struct prod_arg {
        cosmos_strid_t label;
        int       type;
        uintptr_t val;
};


struct prod_args {
        int argc;
        struct prod_arg *argv;
};

struct prod_args *prod_args_new();

int prod_args_add( struct prod_args *, cosmos_strid_t label, int type, uintptr_t arg_val );

struct prod_args *prod_args_from_str( char * );



#endif /* !HIENA_PRODUCER_ARGS_H */
