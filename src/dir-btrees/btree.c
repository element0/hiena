
#include <stdlib.h>
#include "btrees.h"
#include "hierr.h"


btree_t *btree_new(int(*lt)(void *, void *))
{
        btree_t *bt;

        bt = malloc(sizeof(*bt));
        bt->root = bnode_new(NULL);
        bt->garb = bt->root;
        bt->lt = lt;

        return bt;
}


int btree_cleanup( btree_t *bt )
{
        if( bt == NULL )
                return -1;

        bnode_tree_cleanup( bt->garb );
        free( bt );
        return 0;
}

void *btree_get(btree_t *bt, void *key)
{
        //----------
        return NULL;
}

void *btree_put( btree_t *bt, void *k, void *v )
{
        if( bt == NULL )
        {
                HIERR("hiena btree err: 'bt' NULL.");
                return NULL;
        }

        bt->root = bnode_tree_add( bt->root, k, v );
        
        return bt->root;
}

void btree_print( btree_t *bt )
{
	if(bt == NULL)
	{
		HIERR("hiena btree_print called with NULL");
		return;
	}
	bnode_tree_print( bt->root );
}
