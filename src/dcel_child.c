
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
        btree_t *tree, *leaf;



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


