
#include <stdlib.h>
#include "dcel.h"
#include "../hierr.h"

typedef struct hiena_dcel dcel_t;

        /* new dcel(
            server: url.protocol,
            addr: url.addr,
        ) */
dcel_t *dcel_source(char *url) {
    dcel_t *dc = NULL;
        
    if(( dc = dcel_new(NULL) )== NULL )
    {
        HIERR( "dcel_source: new_dcel() returned NULL" );
        goto cleanup;
    }
    return dc;

cleanup:
    dcel_cleanup( dc );

    return NULL;
}

/* ------- OFF */

/* requires m merge_server, dcel_list */
/*
dcel_t *dcel_merge() {

        new dcel(
            server: merge_server,
            addr: dcel_list,
        )
        return NULL;
}
*/

/* requires cosmosexec(), cosmos_executable,
 * args, buf, buffer_server
 *
 */
/*
dcel_t *dcel_process();

    process () {
        new dcel(
            init: exec( fn, args, buf )
            server: buffer_server,
            addr: buf
        )
        return dcel
    }

dcel_t *dcel_mapper(dcel_t *);
    map () {
        run_mapper( mapper, dcel )
        modified dcel's map
        return input dcel
    }

dcel_filehandle *dcel_open();


    open () {
        return handle
    }

----- OFF */
