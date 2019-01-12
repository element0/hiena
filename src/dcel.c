#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include "dcel.h"
#include "hierr.h"
#include "frag.h"
#include "ptr_stack.h"
#include "cosmos.h"

struct hiena_dcel *dcel_new( struct hiena_dcel *dcgarbage )
{
        struct hiena_dcel *dc;

        dc = malloc(sizeof(*dc));
        memset(dc,0,sizeof(*dc));

        return dc;
}


int dcel_cleanup( struct hiena_dcel *dc )
{
        if( dc == NULL )
        {
                HIERR("dcel_cleanup called on a NULL ptr");
                return -1;
        }

        if( dc->retain > 0 )
        {
                dcel_release( dc );
                return 0;
        }
        frag_cleanup( dc->frag );
        free( dc );

        return 0;
}



int dcel_save_undo( struct hiena_dcel *dc )
{
        if( dc == NULL )
        {
                HIERR("dcel_save_undo: err: input dc NULL");
                return -1;
        }

        ptr_stack_t ps;

        ps = dc->undo;

        if( ps == NULL )
        {
                ps =ptr_stack_new();
                dc->undo = ps;
        }

        ptr_stack_push( ps, (void *)dc->frag );

        return 0;
}






/**
    sets a buffer
 */

int dcel_set_val( struct hiena_dcel *dc, void *buf, size_t len )
{
        if( dc == NULL )
        {
                HIERR("dcel_set_val: err: input dc NULL");
                return 0;
        }

        int res;
        struct hiena_frag *f;

        f = dc->frag;

        if( f != NULL )
        {
                dcel_save_undo(dc);
        }

        f = frag_new();
        f->buf = buf;
        f->len = len;

        dc->frag = f;
        dc->dirty = 1;

        return res;
}




struct iovec *dcel_val_ptr(struct hiena_dcel *dc)
{
        struct iovec *iov;

        iov = (struct iovec *)&(dc->frag->buf);

        return iov;
}


