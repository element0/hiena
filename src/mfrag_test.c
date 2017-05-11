








#include "hierr.h"
#include "mfrag.h"

int main( int argc, char *argv[] )
{
        struct hiena_mfrag *m1, *m2;
        int ret;

        m1 = mfrag_new();

        if( mfrag_set_bounds( m1, HIMFRAG_BOUNDS_MIN, HIMFRAG_BOUNDS_MAX ) != 0 ) {
                ret = HIERR( "err frag_set_bounds" );
        }

        if( mfrag_set_bounds( m1, HIMFRAG_BOUNDS_MIN, HIMFRAG_BOUNDS_MAX+1 ) != 0 ) {
                ret = HIERR( "err frag_set_bounds above MAX" );
        }

        if( mfrag_set_bounds( m1, HIMFRAG_BOUNDS_MIN-1, HIMFRAG_BOUNDS_MAX ) != 0 ) {
                ret = HIERR( "err frag_set_bounds below MIN" );
        }

        m2 = mfrag_dup( m1 );

        mfrag_cleanup( m1 );
        mfrag_cleanup( m2 );

        return 0;
}