#ifndef HIENA_ACCESS_FRAME_H
#define HIENA_ACCESS_FRAME_H

#include cosmos.h
#include dcel.h

#define aframe_envar( af, s, len )\
     dcel_child_val( af->env, s, len )

struct access_frame {
        struct cosmos_cosm *cosm;
        struct hiena_dcel *dcel;
        struct hiena_dcel *env;
        struct access_frame *parent;
        btree_t *lookup_cache;
};

struct access_frame *aframe_new();

int aframe_cleanup( struct access_frame * );

#define aframe_envar(af,s,len)\
     dcel_child_val(af->env,s,len)



#endif /* !HIENA_ACCESS_FRAME_H */