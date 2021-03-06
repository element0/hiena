#ifndef _HIENA_DCEL_H_
#define _HIENA_DCEL_H_



/** @file dcel.h
 *
 * CHANGE LOG
 *
 * 2019-12-10 Update
 * - changing `service` to `service_id`
 *
 * 2019-11-30 Update
 * - added `service`
 *
 * 2019-11-28 Fixed
 * - changed `fragmap` to `frag`
 *
 * 2019-03-17 Update
 * - added `bufid`. moved from `mfrag.h`
 * - changed `buffer` to `fragmap`
 * - changed `bufid` to `buffer`
 *
 * 2019-03-16 Update
 * - moved `prod_state` to `prod_instr.h`
 *
 * 2019-02-18 New Version
 * - eliminated dep to cosmos struct
 * - use cosmos_string_db
 * - eleminated child list
 * - use child index for directory
 * - consolidated production state ptrs
 * - removed dep to XSI's iovec
 *
 *
 */

#include "../types.h"

struct prod_instr;
struct cosmos;

#include "frag.h"
#include "mapcel.h"
#include "../btree_cpp.h"
#include "ptr_stack.h"


/**
 * D{omain,irent,ata} Cell
 * A branchable primative for holding generic metadata about a dataset.
 */
struct hiena_dcel {

        /**
         * The producer of the dcel. Includes `module` name
         * and command line arguments. May include multiple
         * instructions.
	 *
	 * Run the prod_instr to generate the dcel.
	 * The module referenced within prod_instr provides
	 * a service API for stream IO.
         */
        struct prod_instr *prod_instr;

	/**
	 * Service module.
	 *
	 * Replace service module ptr with service id.
	 */
	uintptr_t service_id;

	/**
	 * Address
	 */
	void *addr;
	size_t addr_len;

        /**
         * Memory buffer. This can be byte for byte,
         * or can be fragmented.
	 *
	 * The `mfrag` leaves in the
         * `frag` point to locations in the buffer.
         * The actual buffer could contain data in any
         * order.
         */
        void *buffer;
        size_t buffer_len;

        /**
         * A tree of fragments (`frag.h`)
         * which tracks media fragments (`mfrag.h`).
         */
        struct hiena_frag *frag;

        /**
         * Nesting fields within the domain,
         * identified by `mapper` modules.
         */
        struct hiena_mapcel *map;

	/**
	 * Meta properties (or "attributes").
	 */
        btree_t *prop_index;

	/**
	 * Children/Directory Entries. Defines a directory.
	 */
        btree_t *child_index;



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
