#ifndef HIENA_ACCESS_FRAME_H
#define HIENA_ACCESS_FRAME_H

#include <sys/stat.h>
#include "cosmos.h"
/*#include "dcel.h"*/

struct hiena_dcel;

#define aframe_envar(af,s,len)\
     dcel_child_val(af->env,s,len)

struct access_frame {
        struct cosmos *cosmos;
        struct hiena_dcel *cosm;
        struct hiena_dcel *dcel;
        struct hiena_dcel *env;
        struct access_frame *parent;
        btree_t *branch;
        btree_t *lookup_cache;

        struct access_frame *(lookfn)(struct cosmos *, struct access_frame *, char *);
        struct access_frame *(*execfn)(struct access_frame *, int argc, char **);

        struct access_frame *garbage_next;
        struct access_frame *garbage_prev;

        dev_t st_dev;
        mode_t st_mode;
        nlink_t st_nlink;
};

struct access_frame *aframe_new();

int aframe_cleanup( struct access_frame * );

struct access_frame *aframe_lookup(struct access_frame *, char *);

void **aframe_value(struct access_frame *);



#endif /* !HIENA_ACCESS_FRAME_H */
