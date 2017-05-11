#include "mfrag.h"
#include "hiena_svc.h"
#include <stdlib.h>
#include <string.h>


static size_t mfrag_read( void *buf, size_t len, size_t n, struct hiena_fh *fh )
{
        return 0;
}

static size_t mfrag_write( const void *tbd, size_t tbd2, size_t tbd3, struct hiena_fh *fh )
{
        return 0;
}

struct hiena_fh *mfrag_open( void *p, const char *s )
{
        return NULL;
}

static int mfrag_close( struct hiena_fh *fh )
{
        return 0;
}

static int mfrag_seek( struct hiena_fh *fh, long len, int w)
{
        return -1;
}

static int mfrag_getc( struct hiena_fh *fh )
{
        if( fh == NULL )
                return EOF;

        if( fh->is_eof == 1 )
                return EOF;

        if( fh->pos > mf->boundtail
        || fh->pos < mf->boundhead )
        {
                fh->is_eof = 1;
                return EOF;
        }

        int c;
        void *srcfh;
        struct hiena_mfrag *mf;

        mf = (struct hiena_mfrag *)fh->addr;
        srcfh = fh->fh;
 
        c = mf->svc->getc( srcfh );
        fh->pos++;

        return c;
}

int mfrag_io_seek( struct hiena_mfrag_io *mfio, off_t off )
{
        if( ! HIMFRAG_IO_VERIFY( mfio ) )
        {
                return HIERR( "mfrag_io_seek: bad mfrag io object" );
        }
        if( off > HIMFRAG_OFF_MAX || off < HIMFRAG_OFF_MIN )
        {
                return HIERR( "mfrag_io_seek: outside limits" );
        }

        /* 2017-03-24 pos and off types should match */
        mfio->pos += off;

        return 0;
}

size_t mfrag_io_read( struct hiena_mfrag_io *mfio, void *dst, size_t size )
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

size_t mfrag_io_write( struct hiena_mfrag_io *mfio, size_t size );

size_t mfrag_io_append( struct hiena_mfrag_io *mfio, void *buf, size_t len );

size_t mfrag_io_overwrite( struct hiena_mfrag_io *mfio, void *buf, size_t len );

off_t mfrag_io_trim_tail( struct hiena_mfrag_io *mfio, off_t off );

off_t mfrag_io_trim_head( struct hiena_mfrag_io *mfio, off_t off );

int mfrag_io_flush( struct hiena_mfrag_io *mfio );




struct hiena_svc mfrag_svc_ops = {
        .read  = mfrag_read,
        .write = mfrag_write,
        .open  = mfrag_open,
        .close = mfrag_close,
        .seek  = mfrag_seek,
        .getc  = mfrag_getc
};
