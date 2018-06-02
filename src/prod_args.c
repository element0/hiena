
#include <stdlib.h>
#include <strings.h>
#include "cosmos.h"
#include "hierr.h"


struct prod_args *prod_args_new()
{
        struct prod_args *pa;
        struct prod_arg *argv;

        pa = malloc(sizeof(*pa));
        memset(pa,0,sizeof(*pa));
        argv = malloc(sizeof(*argv));
        memset(argv,0,sizeof(*argv));

        pa->argv = argv;

        return pa;
}


void prod_args_cleanup(struct prod_args *args)
{
        free(args->argv);
        free(args);
}


int prod_args_add( struct prod_args *args, cosmos_strid_t label, int type, uintptr_t val )
{
        size_t new_size;
        struct prod_arg *arg;

        new_size = sizeof(struct prod_arg)*(args->argc+1);

        if((args->argv = realloc(args->argv, new_size)) == NULL)
        {
                HIERR("prod_args_add: err: can't allocate.");
                return -1;
        }

        args->argc++;
        arg = (args->argv)[(args->argc)-1];
        arg->label = label;
        arg->type = type;
        arg->val = val;

        return 0;
}


