#ifndef _HIENA_DCEL_H_
#define _HIENA_DCEL_H_



/** @file dcel.h
 *
 * 2018-02-18 New Version
 *
 * CHANGE LOG
 * - eliminate dep to cosmos struct
 * - use cosmos_string_db
 * - eleminate child list
 * - use child index for directory
 * - consolidate production state ptrs
 * - remove dep to XSI's iovec
 *
 * TO CONSIDER
 *
 */

#include "types.h"

struct prod_instr;
#include "frag.h"
#include "mapcel.h"
#include "btree_cpp.h"
#include "ptr_stack.h"



struct hiena_dcel {
        struct prod_instr *prod_instr;

        struct hiena_frag *buffer;
        struct hiena_mapcel *map;

        btree_t *prop_index;
        btree_t *child_index;

        void    *prod_state;


        /* housekeeping */
        int retain;
        int dirty;
        genno_t gen_no;
        genno_t par_gen_no;


        /* undo stack */
        ptr_stack_t undo;
};





/******** housekeeping *******/

/*  dcel.c  */

struct hiena_dcel *dcel_new( struct hiena_dcel * );

#define dcel_retain( dc ) if(dc != NULL) dc->retain++

#define dcel_release( dc ) if(dc != NULL) dc->retain--

int dcel_cleanup( struct hiena_dcel * );



/******** REST API *******/

/*  dcel.c  */

void *dcel_get( struct hiena_dcel *dc, size_t *len );

int dcel_put( struct hiena_dcel *dc, void *buf, size_t len );



/****** Directory *******/

/*  dcel_child.c  */

int dcel_add_child(struct hiena_dcel *, char *, struct hiena_dcel *, struct cosmos *);

struct hiena_dcel *dcel_find_child(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_prefix(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_regex(struct hiena_dcel *, char *, struct cosmos *);

struct hiena_dcel *dcel_find_child_by_ordinal(struct hiena_dcel *, char *, struct cosmos *);


#define dcel_child_val(dc,s,len)\
    r = dcel_child( dcel,varname );\
    val = dcel_read( r, &len );




#endif /*! _HIENA_DCEL_H_ */
