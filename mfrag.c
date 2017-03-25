





#include "mfrag.h"
#include "hierr.h"
#include <stdlib.h>

struct hiena_mfrag *new_mfrag()
{
        struct hiena_mfrag *mf = malloc(sizeof( *mf ));
        return mf;
}

void mfrag_cleanup( struct hiena_mfrag *mf )
{
        if( mf != NULL )
                free( mf );
}

int mfrag_set_bounds( struct hiena_mfrag *f, HIMFRAG_BOUND_T bh, HIMFRAG_BOUND_T bt )
{
        if( f == NULL )
                return 1;
        if(( bh < HIMFRAG_BOUNDS_MIN ) || ( bh > HIMFRAG_BOUNDS_MAX ) ||
( bt > HIMFRAG_BOUNDS_MIN ) ||
( bt > HIMFRAG_BOUNDS_MAX )) {
                return HIERR( "frag_set_bounds: outside limits" );
        }
        f->boundhead = bh;
        f->boundtail = bt;
        return 0;
}

int mfrag_set_src( struct hiena_mfrag *f, HIMFRAG_SRC_T src ) {
        if( f == NULL )
                return 1;
        if( HIMFRAG_SRC_VERIFY( src ) ){
                return HIERR( "mfrag_set_src can't verify src" );
        } 
        f->src = src;
        return 0;
}



int mfrag_io_seek( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off )
{
        if( ! HIMFRAG_IO_VERIFY( mfio ) )
        {
                return HIERR( "mfrag_io_seek: bad mfrag io object" );
        }
        if( off > HIMFRAG_OFF_MAX || off < HIMFRAG_OFF_MIN )
        {
                return HIERR( "mfrag_io_seek: outside limits" );
        }

        /* 20170324 pos and off types should match */
        mfio->pos += off;

        return 0;
}

HIMFRAG_BUFSIZE_T mfrag_io_read( struct hiena_mfrag_io *mfio, void *dst, HIMFRAG_BUFSIZE_T size )
{
        if( ! HIMFRAG_IO_VERIFY( mfio ) )
        {
                return HIERR( "mfrag_io_read: bad mfrag io object" );
        }
        if( dst == NULL )
        {
                return HIERR( "mfrag_io_read: bad dest buffer" );
        }
        if( ! HIMFRAG_SRC_VERIFY( mfio ) )
        {
                return HIERR( "mfrag_io_read: bad src" );
        }
        return 0;
}

HIMFRAG_BUFSIZE_T mfrag_io_write( struct hiena_mfrag_io *mfio, HIMFRAG_BUFSIZE_T size );

HIMFRAG_BUFSIZE_T mfrag_io_append( struct hiena_mfrag_io *mfio, void *buf, HIMFRAG_BUFSIZE_T len );

HIMFRAG_BUFSIZE_T mfrag_io_overwrite( struct hiena_mfrag_io *mfio, void *buf, HIMFRAG_BUFSIZE_T len );

HIMFRAG_OFF_T mfrag_io_trim_tail( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off );

HIMFRAG_OFF_T mfrag_io_trim_head( struct hiena_mfrag_io *mfio, HIMFRAG_OFF_T off );

int mfrag_io_flush( struct hiena_mfrag_io *mfio );

