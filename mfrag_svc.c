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


struct hiena_svc mfrag_svc_ops = {
        .read  = mfrag_read,
        .write = mfrag_write,
        .open  = mfrag_open,
        .close = mfrag_close,
        .seek  = mfrag_seek,
        .getc  = mfrag_getc
};
