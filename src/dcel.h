#ifndef _HIENA_DCEL_H_
#define _HIENA_DCEL_H_

/** @file dcel.h
  2018-05-08:  added child_list
  2018-05-04:  Updated methods to require `struct cosmos *`.
 */

#include <sys/uio.h>
#include "frag.h"
#include "btree_cpp.h"
#include "ptr_stack.h"
#include "mapcel.h"
#include "types.h"
#include "cosmos.h"


struct prod_args;



#define dcel_retain( dc ) if(dc != NULL) dc->retain++


#define dcel_release( dc ) if(dc != NULL) dc->retain--


#define dcel_child_val(dc,s,len)\
    r = dcel_child( dcel,varname );\
    val = dcel_read( r, &len );





struct hiena_dcel {

        /* production */
        /* svc is in producer module */
        int prodfn_id;
        cosmos_strid_t module_id;
        cosmos_strid_t addr;
        struct prod_args *args;

        /* stream and map */
        struct hiena_frag *frag;
        struct hiena_mapcel *mapcel;
        

        /* lists */
        struct dcel_dirent *child_list;
        struct dcel_dirent *child_list_last;


        /* indices */
        btree_t *prop_index;
        btree_t *child_index;

        
        /* production state */
        void    *prop_index_state;
        void    *child_index_state;


        /* housekeeping */
        int retain;
        int dirty;
        genno_t gen_no;
        genno_t par_gen_no;
        ptr_stack_t undo;
};



/* implementation:  dcel.c */


struct hiena_dcel *dcel_new( struct hiena_dcel * );

int dcel_cleanup( struct hiena_dcel * );

struct iovec *dcel_val_ptr(struct hiena_dcel *);


/** sets a buffer
 */
int dcel_set_val( struct hiena_dcel *dc, void *buf, size_t len );



/* implementation:  dcel_child.c */

int dcel_add_child(struct hiena_dcel *, char *, struct hiena_dcel *, struct cosmos *);

struct hiena_dcel *dcel_find_child(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_prefix(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_regex(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_ordinal(struct hiena_dcel *, char *, struct cosmos *);





#endif /*! _HIENA_DCEL_H_ */
