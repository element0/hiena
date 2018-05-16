


#ifndef _HIENA_LOOKUP_HDL_H_
#define _HIENA_LOOKUP_HDL_H_

#include "dcel.h"
#include "access_frame.h"

typedef struct access_frame lookup_target_t;
#define LOOKUP_TARGET_NULL NULL

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

struct lookup_hdl *lookup_hdl_new();
int lookup_hdl_init( struct lookup_hdl *h, struct hiena_dcel *dc, struct hiena_slib *slib );
int lookup_hdl_cleanup(struct lookup_hdl *h);



#endif /* ! _HIENA_LOOKUP_HDL_H_ */
