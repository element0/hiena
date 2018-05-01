#ifndef _HIENA_DCEL_H_
#define _HIENA_DCEL_H_


#include <sys/uio.h>
#include "frag.h"
#include "btree_cpp.h"
#include "prod_instr.h"
#include "ptr_stack.h"
#include "mapcel.h"
#include "types.h"



#define dcel_retain( dc ) dc->retain++


#define dcel_release( dc ) dc->retain--


#define dcel_child_val(dc,s,len)\
    r = dcel_child( dcel,varname );\
    val = dcel_read( r, &len );



/**
    @param index a btree.  keys are ruleids.  values are btrees.  the value btrees are keyed with ruleid values.  the values at the keys are dcel ptrs.

    index[ruleid]
        index[value]
            ptrlist[]

 */

struct hiena_dcel {

        struct prod_instr *prod_instr;
     /* svc is in producer module */

        struct hiena_frag *frag;

        void *scanner_id;
        void *rule_id;

        btree_t *map;
        btree_t *map_index;
     /* xattr stored in map_index */
     /* attr stored in map_index */
     /* exec helper
         referenced in map_index */
        void    *map_index_state;

        btree_t *dir;
        btree_t *dir_index;
        void    *dir_index_state;

        int retain;
        int dirty;
        genno_t gen_no;
        genno_t par_gen_no;

        ptr_stack_t undo;
};


struct hiena_dcel *dcel_new( struct hiena_dcel * );

int dcel_cleanup( struct hiena_dcel * );

struct iovec *dcel_val_ptr(struct hiena_dcel *);


struct hiena_dcel *dcel_find_child(struct hiena_dcel *, char *);

struct hiena_dcel *dcel_find_child_by_prefix(struct hiena_dcel *, char *);

struct hiena_dcel *dcel_find_child_by_regex(struct hiena_dcel *, char *);

struct hiena_dcel *dcel_find_child_by_ordinal(struct hiena_dcel *, char *);


int dcel_set_child(struct hiena_dcel *, char *, struct hiena_mapcel *);



#endif /*! _HIENA_DCEL_H_ */
