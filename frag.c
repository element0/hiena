





#include "frag.h"
#include "hierr.h"
#include <stdlib.h>


struct hiena_frag *frag_split( struct hiena_frag *f, HIFRAG_BOUND_T pos ) {
        HIFRAG_BOUND_T b[4];
        struct hiena_frag *fc[2];

        // does content already have split?

        return NULL;
}


int frag_insert( struct hiena_frag *dstf, struct hiena_frag *srcf, HIFRAG_POS_T pos )
{
        if( dstf == NULL || srcf == NULL )
        {
                return HIERR( "frag_insert: dest frag or fragment to be inserted is null." );
        }

        HIFRAG_POS_T        off, lenf;
        struct hiena_frag  *f0, *f1, *f2, *f3;
        struct hiena_mfrag *m1, *m2;
        HIMFRAG_BOUND_T     mt, mh;

        off = pos;
        f0 = dstf;
        f1 = NULL;
        f2 = srcf;
        f3 = NULL;

frag_insert_start:

        m1 = frag_get_mfrag( f0 );
        if( m1 == NULL )
        {
                /* frag is container */
            
                f1 = frag_get_first_content( f0 );
                if( f1 == NULL )
                        return HIERR( "frag_insert: dest frag contains NULL." );
                goto frag_insert_into_container;
        } else {
                goto frag_insert_into_content;
        }

frag_insert_into_container:

        lenf = frag_get_length( f1 );
 
        if( lenf < off - 1 )
        {
                off =- lenf;
                f1 = frag_get_next( f1 );

                if( f1 == NULL )
                        return HIERR( "frag_insert: insert position is outside of frag." );

                goto frag_insert_into_container;
        }

        if( lenf == off - 1 )
        {
                f2 = srcf;
                f3 = frag_get_next( f1 );

                goto frag_insert_action;
        }

        if( lenf => off )
        {
                f0 = f1;

                goto frag_insert_start;
        }

        return HIERR( "frag_insert: caught unexpected fallthrough at end of frag_insert_into_container.  check my `if` conditions." );


frag_insert_into_content:


        m2 = mfrag_dup( m1 );
        mt = HIFRAG_POS_TO_HIMFRAG_BOUND( pos );
        mh = mt + 1;
        mfrag_set_boundtail( m1, mt );
        mfrag_set_boundhead( m2, mh );

        f1 = new_frag( );
        f3 = new_frag( );
        frag_set_mfrag( f1, m1);
        frag_set_mfrag( f3, m2);
            
        frag_set_first_content( f, f1 );
        frag_set_last_content( f, f3 );

        /* fall through */

frag_insert_action:
        frag_set_next( f1, f2 );
        frag_set_next( f2, f3 );
        frag_set_prev( f3, f2 );
        frag_set_prev( f2, f1 );

        return 0;
}
