#include "dcel.h"
#include <stdio.h>
#include <error.h>

#define DCEL_ERR_INIT \
    int er;

#define DCEL_ERR( e ) perror( e ); \
    er++;

int main() {

    DCEL_ERR_INIT

    struct hiena_dcel *dc =  NULL;
    if(( dc = dcel_new(NULL) )== NULL )
    {
        DCEL_ERR( "err new_dcel()" );
        goto cleanup;
    }

cleanup:
    dcel_cleanup( dc );

    return 0;
}
