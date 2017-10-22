


#ifndef _HIENA_LOOKUP_HDL_H_
#define _HIENA_LOOKUP_HDL_H_

#include "dcel.h"
#include "slib.h"

struct lookup_hdl
{
        struct hiena_dcel *target;
        char *lookup_str;
        struct hiena_slib *scanlib;
        struct hiena_dcel *result;
        

        int (*set_target)( struct lookup_hdl *, struct hiena_dcel * );

        struct hiena_dcel *(*find_child)( struct lookup_hdl *, char * );

        struct hiena_dcel *(*find_prop)( struct lookup_hdl *, char * );

        struct hiena_dcel *(*grind)( struct lookup_hdl *, char * );
};



#endif /* ! _HIENA_LOOKUP_HDL_H_ */