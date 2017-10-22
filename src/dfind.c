

#include <stdio.h>
#include <stdlib.h>
#include "context_frame.h"
#include "dcel.h"


static void *index_child_in_list( struct ptr_array *pa )
{
        return NULL;
}


struct hiena_dcel *dfind_child( struct context_frame *cx, int argc, void **argv)
{
        if( argv == NULL )
        {
                HIERR("dfind_child: err: argv NULL");

                return NULL;
        }

        struct hiena_dcel *chd;

        chd = DFIND_CHILD_IN_INDEX;
        if( chd != NULL )
        {
                return chd;
        }

        INDEX_CHILD_IN_LIST;

        if(CANT_FIND_CHILD_IN_INDEX)
        {
                return NULL;
        }

        chd = DFIND_CHILD_IN_INDEX;

        return chd;
}



struct hiena_dcel *dfind_prop( struct context_frame *cx, int argc, void **argv)
{
        if( argv == NULL )
        {
                HIERR("dfind_prop: err: argv NULL");

                return NULL;
        }
        return NULL;
}