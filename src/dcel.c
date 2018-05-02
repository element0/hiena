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


struct iovec *dcel_val_ptr(struct hiena_dcel *dc)
{
        struct iovec *iov;

        iov = (struct iovec *)&(dc->frag->buf);

        return iov;
}


static int split_prefix( struct dcel_dirent *e )
{
        char *c, *prefix, *suffix;
        char *name;
        size_t ct, len;

        if( e == NULL )
        {
                HIERR("dcel::split_prefix: err e NULL");
                return -1;
        }


        name = e->d_name;
        prefix = e->prefix;
        suffix = e->suffix;

        if( name == NULL )
        {
                HIERR("dcel::split_prefix: err incoming name NULL");
                return -1;
        }

        if( prefix != NULL )
        {
                HIERR("dcel::split_prefix: err incoming prefix ptr is not initialized.  please initialize to NULL");
                return -1;
        }

        if( suffix != NULL )
        {
                HIERR("dcel::split_prefix: err incoming suffix ptr is not initialized.  please initialize to NULL");
                return -1;
        }



        /* prefix up to '.' */

        c = name;

        len = strlen(name);

        while( *c != '.' 
            && *(c++) != '\0'
            && ct++ <= len );

        prefix = strndup(name, ct);



        /* suffix incl '.' */

        len = strlen(c);

        if( len > 0 )
        {
                suffix = strndup(c, len);
        }else{
                suffix = NULL;
        }

        e->prefix = prefix;
        e->suffix = suffix;

        return 0;
}

int dcel_set_child(struct hiena_dcel *dc, char *name, struct hiena_mapcel *mc, struct cosmos *cm)
{
        if(dc == NULL)
        {
                HIERR("dcel_set_child: err: dc NULL");
                return -1;
        }

        if(name == NULL)
        {
                HIERR("dcel_set_child: err: name NULL");
                return -1;
        }

        if(mc == NULL)
        {
                HIERR("dcel_set_child: err: mc NULL");
                return -1;
        }

        if(cm == NULL)
        {
                HIERR("dcel_set_child: err: mc NULL");
                return -1;
        }

        if(dc->dir == NULL)
        {
                HIERR("dcel_set_child: err: dc->dir is NULL.");

                return -1;
        }



        struct dcel_dirent e;
        cosmos_strid_t id;
        btree_t *tree, *leaf;



        e.d_name = name;
        e.suffix = NULL;
        e.prefix = NULL;



        split_prefix(&e);




        tree = dc->dir;

        id = cosmos_put_string(cm, e.prefix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_set_child: err: prefix string id NULL");
                goto abort;
        }





        leaf = (btree_t *)btree_get(tree, id);


        if( leaf == NULL )
        {
                leaf = btree_new();
                btree_put(tree, id, (bval_t)leaf);

        }else{

                err = btree_get(leaf, suffix);
                if( err != NULL )
                {
                        HIERR("dcel_set_child: err: child entry exists.");
            
                        goto abort;
                }
        }




        id = cosmos_put_string(cm, e.suffix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_set_child: err: suffix string id NULL");
                goto abort;
        }



        btree_put(leaf, id, (bval_t)mc);


        free(e.prefix);
        free(e.suffix);

        return 0;

abort:
        free(e.prefix);
        free(e.suffix);

        return -1;
}


