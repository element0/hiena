

/* dcel_child.c
   2018-05-08 add linked list
 */

#include <errno.h>
#include <string.h>
#include "dcel_dirent.h"
#include "dcel.h"
#include "cosmos.h"
#include "hierr.h"
#include "btree_cpp.h"


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


int dcel_add_child( struct hiena_dcel *par, char *name, struct hiena_dcel *child, struct cosmos *cm )
{
        if(par == NULL)
        {
                HIERR("dcel_add_child: err: par NULL");
                return -1;
        }

        if(name == NULL)
        {
                HIERR("dcel_add_child: err: name NULL");
                return -1;
        }

        if(child == NULL)
        {
                HIERR("dcel_add_child: err: child NULL");
                return -1;
        }

        if(cm == NULL)
        {
                HIERR("dcel_add_child: err: cm NULL");
                return -1;
        }

        if(par->child_index == NULL)
        {
                par->child_index = btree_new();
        }



        struct dcel_dirent e, *ce;
        struct dcel_dirent *first, *last;
        cosmos_strid_t id, id2;
        btree_t *tree, *leaf;






        /* set complex index */





        e.d_name = name;
        e.suffix = NULL;
        e.prefix = NULL;
        e.next = NULL;
        e.next_same = NULL;



        split_prefix(&e);




        tree = par->child_index;

        id = cosmos_put_string(cm, e.prefix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_add_child: err: prefix string id NULL");
                goto abort;
        }

        id2 = cosmos_put_string(cm, e.suffix);

        /* suffix id NULL OK */


        ce = NULL;


        leaf = (btree_t *)btree_get(tree, (bkey_t)id);

        if( leaf == NULL )
        {
                leaf = btree_new();
                btree_put(tree, (bkey_t)id, (bval_t)leaf);
        }


        else {
                ce = (struct dcel_dirent *)btree_get(leaf, (bkey_t)id2);
        }


        if( ce == NULL )
        {
                ce = malloc(sizeof(*ce));
                memset(ce,0,sizeof(*ce));

                btree_put(leaf, (bkey_t)id2,(bval_t)ce);

        }

        else {

                for(; ce->next_same != NULL; ce = ce->next_same);

                ce->next_same = malloc(sizeof(*ce));
                memset(ce->next_same,0,sizeof(*ce));


                ce = ce->next_same;

        }


        ce->dcel = child;






        /* set simple list */





        first = par->child_list;
        if( first == NULL )
        {
                par->child_list = ce;
                first = ce;
        }

        last = par->child_list_last;
        if( last != NULL )
        {
                last->next = ce;
        }

        else {
                last = ce;
        }


        free(e.prefix);
        free(e.suffix);

        return 0;

abort:
        HIERR("dcel_add_child: abort");
        free(e.prefix);
        free(e.suffix);

        return -1;
}




/** return a new dcel w list in dcel->child */

struct hiena_dcel *dcel_find_child(struct hiena_dcel *par, char *name, struct cosmos *cm)
{
        if(par == NULL)
        {
                HIERR("dcel_find_child: err: par NULL");
                return NULL;
        }

        if(name == NULL)
        {
                HIERR("dcel_find_child: err: name NULL");
                return NULL;
        }

        if(cm == NULL)
        {
                HIERR("dcel_find_child: err: cm NULL");
                return NULL;
        }

        if( par->child_index == NULL )
        {
                HIERR("dcel_find_child: err: par->child_index NULL");
                return NULL;
        }


        struct hiena_dcel *dc;
        struct dcel_dirent e, *child;
        cosmos_strid_t id;
        btree_t *prefix_tree, *suffix_tree;
        int err;


        e.d_name = name;
        e.suffix = NULL;
        e.prefix = NULL;

        split_prefix(&e);



        prefix_tree = par->child_index;


        id = cosmos_string_id(e.prefix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_find_child: err: prefix string id NULL");

                goto abort;
        }


        suffix_tree = (btree_t *)btree_get(prefix_tree, (bkey_t)id);


        if( suffix_tree == NULL )
        {
                HIERR("dcel_find_child: err: prefix ENOENT.");

                err = ENOENT;

                goto abort;
        }



        /* (NULL is a valid id) */

        id = cosmos_string_id( e.suffix );




        child = (struct dcel_dirent *)btree_get(suffix_tree, (bkey_t)id);

        if( child == NULL )
        {
                HIERR("dcel_find_child: err: child NULL, ENOENT");

                err = ENOENT;

                goto abort;
        }

        if( child->dcel == NULL )
        {
                HIERR("dcel_find_child: err: child->dcel NULL, ENOENT");

                err = ENOENT;

                goto abort;
        }


        free(e.prefix);
        free(e.suffix);

        dc = dcel_new(cm->dcel_garbage);

        for(;child != NULL && child->dcel != NULL;child = child->next_same)
        {
        dcel_add_child(dc, name, child->dcel, cm);
        }
        

        return dc;

abort:
        free(e.prefix);
        free(e.suffix);

        return NULL;
}

struct hiena_dcel *dcel_find_child_by_prefix(struct hiena_dcel *par, char *name, struct cosmos *cm)
{
        return NULL;
}

struct hiena_dcel *dcel_find_child_by_regex(struct hiena_dcel *par, char *restr, struct cosmos *cm)
{
        return NULL;
}

struct hiena_dcel *dcel_find_child_by_ordinal(struct hiena_dcel *par, char *ord, struct cosmos *cm)
{
        return NULL;
}
