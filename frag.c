





#include "frag.h"
#include "hierr.h"
#include <stdlib.h>


struct hiena_frag *frag_split( struct hiena_frag *f, HIFRAG_BOUND_T pos ) {
        HIFRAG_BOUND_T b[4];
        struct hiena_frag *fc[2];

        // does content already have split?

        return NULL;
}

int frag_insert( struct hiena_frag *f, struct hiena_mfrag *mf, HIFRAG_BOUND_T pos ) {
        if( f == NULL || mf == NULL ) {
                return HIERR( "frag_insert: frag or media fragment to be inserted is null." );
        }
        HIFRAG_BOUND_T cursor = 0;
        return -1;
}
