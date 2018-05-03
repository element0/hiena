#ifndef _HIENA_DCEL_H_
#define _HIENA_DCEL_H_

/** @file dcel.h

  2018-05-04:  Updated methods to require `struct cosmos *`.
 */

#include <sys/uio.h>
#include "frag.h"
#include "btree_cpp.h"
#include "prod_instr.h"
#include "ptr_stack.h"
#include "mapcel.h"
#include "types.h"
#include "cosmos.h"



#define dcel_retain( dc ) dc->retain++


#define dcel_release( dc ) dc->retain--


#define dcel_child_val(dc,s,len)\
    r = dcel_child( dcel,varname );\
    val = dcel_read( r, &len );



/**
    Updated 2018-05-04

    @param prop is a btree keyed by scanner rule ids; its values are btrees.
    the value btrees are keyed with rule values.  the leaf values are mapcel ptr lists.

    <pre>
    prop[ruleid]
        index[rule_value]
            ptrlist[]
    </pre>

    @param child 

    <pre>
    child[ prefix str id ]
        suffix[ suffix str id ]
            dcel ptr
    </pre>

    
 */

struct hiena_dcel {

        /** production */
        
        /* svc is in producer module */

        struct prod_instr *prod_instr;


        /** stream and map */

        struct hiena_frag *frag;
        struct hiena_mapcel *mapcel;
        
        /** map and index */

        /** properties stored in prop index
          - attr
          - xattr
          - scanner_id
          - rule_id
          - exec heler reference
          */

        btree_t *prop;  /* index */
        btree_t *child; /* index */

        
        /** production state */
        void    *prop_index_state;
        void    *child_index_state;

        /** housekeeping */
        int retain;
        int dirty;
        genno_t gen_no;
        genno_t par_gen_no;
        ptr_stack_t undo;
};


struct hiena_dcel *dcel_new( struct hiena_dcel * );

int dcel_cleanup( struct hiena_dcel * );

struct iovec *dcel_val_ptr(struct hiena_dcel *);


/*
  dcel_child.c
 */

int dcel_add_child(struct hiena_dcel *, char *, struct hiena_dcel *, struct cosmos *);

struct hiena_dcel *dcel_find_child(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_prefix(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_regex(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_ordinal(struct hiena_dcel *, char *, struct cosmos *);





#endif /*! _HIENA_DCEL_H_ */
