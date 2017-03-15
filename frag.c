#include "frag.h"
#include "hierr.h"
#include <stdlib.h>

struct hiena_frag *new_frag() {
    struct hiena_frag *f = malloc(sizeof( *f ));
    return f;
}



void frag_cleanup( struct hiena_frag *f ) {
        if( f != NULL )
                free( f );
}

int frag_set_bounds( struct hiena_frag *f, HIFRAG_BOUND_T bh, HIFRAG_BOUND_T bt ) {
        if( f == NULL )
                return 1;
        if(( bh < HIFRAG_BOUNDS_MIN ) || ( bh > HIFRAG_BOUNDS_MAX ) ||
( bt > HIFRAG_BOUNDS_MIN ) ||
( bt > HIFRAG_BOUNDS_MAX )) {
                return HIERR( "frag_set_bounds: outside limits" );
        }
        f->boundhead = bh;
        f->boundtail = bt;
        return 0;
}

int frag_set_src( struct hiena_frag *f, HIFRAG_SRC_T src ) {
        if( f == NULL )
                return 1;
        if( HIFRAG_SRC_VERIFY( src ) ){
                return HIERR( "frag_set_src can't verify src" );
        } 
        f->src = src;
        return 0;
}

struct hiena_frag *frag_split( struct hiena_frag *f, HIFRAG_BOUND_T pos ) {
        HIFRAG_BOUND_T b[4];
        struct hiena_frag *fc[2];
        return NULL;
}