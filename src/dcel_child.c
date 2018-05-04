#include <errno.h>

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

        if(par->dir == NULL)
        {
                HIERR("dcel_add_child: err: par->dir is NULL.");

                return -1;
        }



        struct dcel_dirent e;
        cosmos_strid_t id;
        btree_t *tree, *leaf, *err;



        e.d_name = name;
        e.suffix = NULL;
        e.prefix = NULL;



        split_prefix(&e);




        tree = par->child;

        id = cosmos_put_string(cm, e.prefix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_add_child: err: prefix string id NULL");
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
                        HIERR("dcel_add_child: err: child entry exists.");
            
                        goto abort;
                }
        }




        id = cosmos_put_string(cm, e.suffix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_add_child: err: suffix string id NULL");
                goto abort;
        }



        btree_put(leaf, id, (bval_t)child);


        free(e.prefix);
        free(e.suffix);

        return 0;

abort:
        free(e.prefix);
        free(e.suffix);

        return -1;
}

/** TEMP:  this only returns the first match 
          if there are multiple children all with the 
          same name. */

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

        if( par->child == NULL )
        {
                HIERR("dcel_find_child: err: par->child NULL");
                return NULL;
        }
        
        struct dcel_dirent e, *child;
        cosmos_strid_t id;
        btree_t *prefix_tree, *suffix_tree;
        int err;


        e.d_name = name;
        e.suffix = NULL;
        e.prefix = NULL;

        split_prefix(&e);



        prefix_tree = par->child;


        id = cosmos_string_id(cm, e.prefix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_find_child: err: prefix string id NULL");

                goto abort;
        }


        suffix_tree = (btree_t *)btree_get(prefix_tree, id);


        if( suffix_tree == NULL )
        {
                HIERR("dcel_find_child: err: prefix ENOENT.");

                err = ENOENT;

                goto abort;
        }



        id = cosmos_string_id(cm, e.suffix);

        if( id == COSMOS_STRID_NULL)
        {
                HIERR("dcel_find_child: err: suffix string id NULL");

                goto abort;
        }



        child = (struct dcel_dirent *)btree_get(suffix_tree, id);

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



        return child->dcel;

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

struct hiena_dcel *dcel_find_child_by_ordinal(struct hiena_dcel *, char *, struct cosmos *)
{
        return NULL;
}
