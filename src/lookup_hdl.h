


#ifndef _HIENA_LOOKUP_HDL_H_
#define _HIENA_LOOKUP_HDL_H_

#include "dcel.h"
#include "access_frame.h"

typedef struct access_frame lookup_target_t;

typedef void lookup_result_t;

struct lookup_hdl
{
        lookup_target_t *target;
        lookup_result_t *result;
        char *str;
        struct cosmos *cosmos;
        struct access_frame *aframe;
        struct hiena_dcel *cosm;

        int (*set_target)( struct lookup_hdl *, lookup_target_t * );

        lookup_target_t *(*find_child)( struct lookup_hdl *, char * );

        lookup_target_t *(*find_prop)( struct lookup_hdl *, char * );

        int (*step_segment)( struct lookup_hdl * );


        lookup_result_t *(*exec)( void * );


};



#endif /* ! _HIENA_LOOKUP_HDL_H_ */