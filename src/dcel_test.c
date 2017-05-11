#include dcel.h
#include <stdio.h>

#define DCEL_ERR( e ) perror( e ); \
    er++;

int dcel_test() {

    hiena_dcel *dc =  NULL;
    if(( dc = new_dcel() )== NULL ) {
        DCEL_ERR( "err new_dcel()" );
        goto cleanup;
    }

cleanup:
    dcel_cleanup( dc );

    return 0;
}
