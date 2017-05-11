#include "mfrag.h"
#include "hiena_svc.h"
#include <stdlib.h>
#include <string.h>


#include "mfrag_fh.h"
#include "hiena_fh.h"


struct hiena_fh *mfrag_fh_open( struct hiena_mfrag *mf, const char *mode )
{
        if( mf == NULL )
                return NULL;

        struct hiena_fh *fh, srcfh;

        fh    = hiena_fh_new();
        srcfh = hiena_fh_new();

        srcfh->ops = mf->svc;
        srcfh->addr = mf->addr;
        srcfh->fh = mf->svc->open( mf->addr, mode );

        /* mfrag_svc_ops defined in mfrag_svc.c */

        fh->addr = (void *)mf;
        fh->ops  = &mfrag_svc_ops;
        fh->fh   = srcfh;
        fh->pos  = 0;
        fh->is_eof = 0;

        return fh;
}

int frag_fh_close( struct hiena_fh *fh )
{
        if( fh == NULL )
                return 0;

        struct mfrag_fh *mfh;
        struct hiena_fh *srcfh;

        mfh = fh->fh;
        srcfh = mfh->fh;

        srcfh->ops->close( srcfh->fh );

        hiena_fs_cleanup( srcfh );
        mfrag_fh_cleanup( fh->fh );
        hiena_fh_cleanup( fh );

        return 0;
}