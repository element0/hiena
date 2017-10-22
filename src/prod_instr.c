#include <stdlib.h>
#include <string.h>
#include "prod_instr.h"


struct prod_instr *prod_instr_new()
{
        prod_instr *pi;

        pi = malloc(sizeof(*pi));
        memset(pi,0,sizeof(*pi));

        return pi;
}


int prod_instr_cleanup(struct prod_instr *pi)
{
        if( pi == NULL )
        {
                HIERR("prod_instr_cleanup: err: pi NULL");
                return -1;
        }

        struct ptr_stack *p;
        struct linked_item *top;

        free(pi);

        return 0;
}