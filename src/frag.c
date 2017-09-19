



#include <stdlib.h>
#include <string.h>

#include "frag.h"
#include "hierr.h"
#include "btrees.h"


struct hiena_frag *new_frag()
{
        return frag_new();
}


struct hiena_frag *frag_new()
{
        struct hiena_frag *f;
        f = malloc(sizeof(*f));
        memset(f,0,sizeof(*f));

        f->anchors = btree_new();
        f->children = NULL;

        return f;
}


int frag_cleanup ( struct hiena_frag *f )
{
        if( f == NULL )
                return -1;

        btree_cleanup(f->anchors);

        free( f );

        return 0;
}


// ---- old ----

int frag_set_first_content( struct hiena_frag *f, struct hiena_frag *fc )
{
        if( f == NULL )
                return -1;

        f->first_content = fc;

        return 0;
}

struct hiena_frag *frag_get_first_content( struct hiena_frag *f )
{
        if( f == NULL )
        {
                return HIERR( "frag_get_first_content: frag is null." ), NULL;
        }

        struct hiena_frag *f1;
        f1 = f->first_content;

        if( f1 == NULL )
        {
                return HIERR( "frag_get_first_content: content is null." ), NULL;
        }

        return f1;
}

int frag_set_last_content( struct hiena_frag *f, struct hiena_frag *lc )
{
        if( f == NULL )
                return -1;

        f->last_content = lc;

        return 0;
}

int frag_set_next( struct hiena_frag *f, struct hiena_frag *f2 )
{
        if( f == NULL )
                return -1;

        f->next = f2;

        return 0;
}


struct hiena_frag *frag_get_next( struct hiena_frag *f )
{
        if( f == NULL )
        {
                return HIERR( "frag_get_next: frag is null." ), NULL;
        }

        struct hiena_frag *f1;
        f1 = f->next;

        if( f1 == NULL )
        {
                return HIERR( "frag_get_next: content is null." ), NULL;
        }

        return f1;
        
}

int frag_set_prev( struct hiena_frag *f, struct hiena_frag *f2 )
{
        if( f == NULL )
                return -1;

        f->prev = f2;

        return 0;
}

//---- mfrag ----

int frag_set_mfrag( struct hiena_frag *f, struct hiena_mfrag *mf )
{
        if( f == NULL )
                return -1;
        f->mfrag = mf;
        return 0;
}

struct hiena_mfrag *frag_get_mfrag( struct hiena_frag *f )
{
        if( f == NULL )
        {
                return HIERR( "frag_get_mfrag: frag is null." ), NULL;
        }
        struct hiena_mfrag *mf;
        mf = f->mfrag;

        return mf;
}


//---- mapping ----

struct hiena_frag *frag_split( struct hiena_frag *f, HIFRAG_POS_T pos ) {
        HIFRAG_BOUND_T b[4];
        struct hiena_frag *fc[2];

        // does content already have split?

        return NULL;
}

//---- meta ----

/* TODO: frag_get_length
   Have the scanner system journal the length into the frag.
   Otherwise, this re-traces the entire domain. - rh
 */

HIFRAG_POS_T frag_get_length( struct hiena_frag *f )
{
        if( f == NULL )
        {
                return HIERR( "frag_get_length: frag is null." );
        }

        HIFRAG_POS_T len;
        struct hiena_frag *f1;
        struct hiena_mfrag *m1;

        m1 = frag_get_mfrag( f );
        if( m1 == NULL )
        {
                f1 = frag_get_first_content( f );

                len = frag_get_length( f1 );

                while(( f1 = frag_get_next( f1 )) != NULL )
                {
                        len =+ frag_get_length( f1 );
                }
        } else {
                len = mfrag_get_length( m1 );
        }
        return len;
}


//---- mapping ----

int frag_insert( struct hiena_frag *dstf, struct hiena_frag *srcf, HIFRAG_POS_T pos )
{
        HIFRAG_POS_T  off, lenf;
        HIMFRAG_BOUND_T  mt, mh;
        struct hiena_frag  *f0, *f1, *f2, *f3;
        struct hiena_mfrag *m1, *m2;


        if( dstf == NULL
         || srcf == NULL )
        {
                return HIERR( "frag_insert: dest frag or fragment to be inserted is null." );
        }

        
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

        if( lenf >= off )
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
        frag_set_mfrag( f0, NULL);
            
        frag_set_first_content( f0, f1 );
        frag_set_last_content( f0, f3 );

        /* fall through */

frag_insert_action:
        frag_set_next( f1, f2 );
        frag_set_next( f2, f3 );
        frag_set_prev( f3, f2 );
        frag_set_prev( f2, f1 );

        return 0;
}


int frag_put_anchor( struct hiena_frag *f, size_t pos, struct map_anchor *ma )
{
        if( f == NULL )
        {
                HIERR("frag_put_anchor: err: f NULL");
                return -1;
        }

        btree_t *b;
        void *er;

        b = f->anchors;

        if( b == NULL )
        {
                HIERR("frag_get_anchor: err: f->anchors NULL");
                return NULL;
        }

        er = btree_put( b, (void *)pos, (void *)ma );

        return 0;
}


struct map_anchor *frag_get_anchor( struct hiena_frag *f, size_t pos )
{
        if( f == NULL )
        {
                HIERR("frag_get_anchor: err: f NULL");
                return NULL;
        }
        btree_t *b;
        struct map_anchor *ma;

        b = f->anchors;

        if( b == NULL )
        {
                HIERR("frag_get_anchor: err: f->anchors NULL");
                return NULL;
        }

        ma = (struct map_anchor *)btree_get(b,(void *)pos);

        

        return ma;
}
