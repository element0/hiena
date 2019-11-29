#include <stdio.h>
#include <error.h>
#include "dcel.h"
#include "data_cell.h"

#define DCEL_ERR_INIT \
    int er;

#define DCEL_ERR( e ) perror( e ); \
    er++;

int main() {

    DCEL_ERR_INIT;

    struct hiena_dcel *dc =  NULL;
    if(( dc = dcel_source(NULL) )== NULL )
    {
        DCEL_ERR( "err main:dcel_source() returned NULL" );
        goto cleanup;
    }

    fprintf(stderr,"data_cell_test: OK");

cleanup:
    dcel_cleanup( dc );

    return 0;
}
