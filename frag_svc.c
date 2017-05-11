#include "mfrag.h"
#include "frag.h"
#include "hiena_svc.h"
#include <stdlib.h>
#include <string.h>


static size_t frag_read( void *buf, size_t len, size_t n, struct hiena_fh *fh )
{
        return 0;
}

static size_t frag_write( const void *tbd, size_t tbd2, size_t tbd3, struct hiena_fh *fh )
{
        return 0;
}

struct hiena_fh *frag_open( void *p, const char *s )
{
        return NULL;
}

static int frag_close( struct hiena_fh *fh )
{
        return 0;
}

static int frag_seek( struct hiena_fh *fh, long len, int w)
{
        return -1;
}

static int frag_getc( struct hiena_fh *fh )
{
        struct hiena_frag *f, f0;

        f = (struct hiena_frag *)fh->addr;
       //---------------------

        return EOF;
}


struct hiena_svc frag_svc_ops = {
        .read  = frag_read,
        .write = frag_write,
        .open  = frag_open,
        .close = frag_close,
        .seek  = frag_seek,
        .getc  = frag_getc
};
