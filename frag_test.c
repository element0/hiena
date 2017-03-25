#include "hierr.h"
#include "frag.h"
#include <stdio.h>
#include <stdlib.h>

int frag_test() {
        int ret = 0;
        struct hiena_frag *f = NULL;

        if(( f = new_frag() ) == NULL ) {
                ret = HIFRAG_ERR( "err new_frag, abort tests" );
                goto end;
        }

        if( frag_set_bounds( f, HIFRAG_BOUNDS_MIN, HIFRAG_BOUNDS_MAX ) != 0 ) {
                ret = HIFRAG_ERR( "err frag_set_bounds" );
        }

        if( frag_set_bounds( f, HIFRAG_BOUNDS_MIN, HIFRAG_BOUNDS_MAX+1 ) != 0 ) {
                ret = HIFRAG_ERR( "err frag_set_bounds above MAX" );
        }

        if( frag_set_bounds( f, HIFRAG_BOUNDS_MIN-1, HIFRAG_BOUNDS_MAX ) != 0 ) {
                ret = HIFRAG_ERR( "err frag_set_bounds below MIN" );
        }

cleanup:
        frag_cleanup( f );
end:
        return ret;
}