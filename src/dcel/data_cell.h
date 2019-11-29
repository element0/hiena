#ifndef _HIENA_DATA_CELL_H_
#define _HIENA_DATA_CELL_H_

typedef struct hiena_dcel dcel_t;

/** @file data_cell.h
 *
 * Public API for working with dcels.
 *
 */


/**
 * Makes a new dcel with source address
 * and service. The result can be opened
 * for io, combined, mapped or processed.
 */

dcel_t *dcel_source(char *);


/**
 * Combines multiple dcels in various
 * formations.
 *
 * Requires merge_server, dcel_list.
 */

dcel_t *dcel_merge();



/**
 * Process a dcel through a cosmos
 * executable. The results depend on the
 * executable.
 *
 * Returns dcel if modified, a new dcel if
 * generated.
 *
 * Requires cosmosexec(), cosmos_executable,
 * args, buf, buffer_server.
 */

dcel_t *dcel_process();


/**
 * Scan and map a dcel with a cosmos
 * executable.
 *
 * Modifies and returns the dcel.
 */

dcel_t *dcel_scan(dcel_t *);


/**
 * Returns a handle for stream io.
 *
 * IO methods are defined in the handle
 * component.
 */

void *dcel_open();





#endif /*! _HIENA_DATA_CELL_H_ */
