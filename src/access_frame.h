#ifndef HIENA_ACCESS_FRAME_H
#define HIENA_ACCESS_FRAME_H

/** @file access_frame.h
 *
 *  Consider renaming as "path_node.h".
 */

#include <sys/stat.h>
#include "cosmos.h"

struct hiena_dcel;

#define aframe_envar(af,s,len)\
     dcel_child_val(af != NULL ? af->env : NULL, s, len)


struct access_frame {

        /**
         * 2019-03-05 1958
         * Depricated in favor of a generic
         * payload.
         */
        struct hiena_dcel *dcel;

        /**
         * A generic payload allows
         * pathnodes to locate any type of
         * object.
         */
        void *payload;

        /**
         * Parent path node.
         */
        struct access_frame *parent;


        /**
         * This is how we facilitate
         * inheritance. Consider renaming
         * "inheritance".
         * The access_frame does
         * not implement the inheritance 
         * functions. The cosmos filesystem 
         * will provide them. 
         */
        struct access_frame *cascade;

        /**
         * The number of inheritance 
         * sources.
         * Usually 0 or 1. Greater than 1
         * defines multiple inheritances.
         */
        int cascade_count;

        /**
         * Path branches. CosmosFS uses
         * these for lookup request cache.
         * Dirents are implemented by `dcel->index`.
         *
         */
        btree_t *branch;


        /**
         * Consider implementing in
         * '.cosm'.
         */
        struct access_frame *lookfn_hdl;

        /**
         * Consider implementing in
         * '.cosm'.
         */
        struct access_frame *(*lookfn)(struct cosmos *, struct access_frame *, char *);

        /**
         * Consider implementing in
         * '.cosm'.
         */
        struct access_frame *(*execfn)(struct access_frame *, int argc, char **);

        /**
         * Consider implementing in
         * '.cosm'.
         */
        int execfnid;


        struct access_frame *garbage_next;
        struct access_frame *garbage_prev;

        dev_t st_dev;
        mode_t st_mode;
        nlink_t st_nlink;
};

struct access_frame *aframe_new();

struct access_frame *aframe_spawn(struct access_frame *);

int aframe_cleanup( struct access_frame * );

struct access_frame *aframe_lookup(struct access_frame *, char *);


struct access_frame *aframe_set_branch(struct access_frame *, cosmos_strid_t, struct access_frame *);

struct access_frame *aframe_get_branch(struct access_frame *, cosmos_strid_t);



/**
    an aframe, via it's dcel, can refer to an internal location within another resource.
  some resources will need to be opened before they can be used.  (the resource type
  and handler module are managed within the dcel.)

  */

int aframe_open_value(struct access_frame *);




/**

DANGEROUS: the returned iovec contains a raw pointer to the internal buffer of the dcel behind the aframe.  This method is included for efficiency, but please be careful.

 */
struct iovec *aframe_get_value_iovec(struct access_frame *);




/**
    copies bytes (nmemb*size) from aframe's internal value into ptr.

 */
size_t aframe_read_value(void *ptr, size_t size, size_t nmemb, struct access_frame *);

int aframe_close_value(struct access_frame *);



/*    retire this and use 'aframe_get_value'

struct iovec *aframe_val_ptr(struct access_frame *);

*/



bval_t  aframe_remap_dirent_id( struct access_frame *, bval_t );


int aframe_set_parent(struct access_frame *, struct access_frame *);





/**
    This is a dirty shortcut.  The nice way to do it is cosmos_bind().
 */

int aframe_set_value_ptr(struct access_frame *, void *);

void *aframe_get_value_ptr(struct access_frame *);



#endif /* !HIENA_ACCESS_FRAME_H */
