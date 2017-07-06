/* WORK IN PROGRESS:
   binary tree 4-26-2015
   complete re-write 10-30-2015
   modularized 06-05-2017
   */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "btrees.h"
#include "hierr.h"


bnode_t *bnode_new ( bnode_t *garbage )
{
        struct bnode *bn;

        bn = malloc(sizeof(*bn));
        memset(bn, 0, sizeof(*bn));

    /* note if EMPTY is defined as anything BESIDES 0
       you will need to set all keys EMPTY now */

        if(garbage != NULL)
        {
                bn->garbage = garbage->garbage;
                garbage->garbage = bn;
        }
    
        return bn;
}

void bnode_print (bnode_t *node)
{
        int i;
        printf("p%lu [label=\"keys: ",  (long unsigned int)node);

        for(i=0; i<NUM_KEYS; i++)
                printf("%lu:%lu ", (long unsigned int)node->key[i], (long unsigned int)node->val[i]);

        printf("\"];\n");

        for(i=0; i<=NUM_KEYS && node->link[i] != NULL; i++)
                printf("p%lu -> p%lu;\n", (long unsigned int)node, (long unsigned int)node->link[i]);
}

void bnode_cleanup (bnode_t *bn)
{
        free(bn);
}

void bnode_init_root (bnode_t *root_n)
{
        if(root_n != NULL)
                root_n->key[0] = (bkey_t)ROOTKEY;
}

void bnode_tree_print (bnode_t *root_n)
{
        bnode_t *cur_n = root_n;
        bnode_t *next_n;
        while(cur_n != NULL)
        {
                next_n = cur_n->garbage;
                bnode_print(cur_n);
                cur_n = next_n;
        }
}

void bnode_tree_cleanup (bnode_t *root_n)
{
        bnode_t *cur_n = root_n;
        bnode_t *next_n;
        while(cur_n != NULL)
        {
                next_n = cur_n->garbage;
                bnode_cleanup(cur_n);
                cur_n = next_n;
        }
}

static int set_garbage (bnode_t *dst, bnode_t *src)
{
        if(src == NULL
        || dst == NULL)
        {
                HIERR("hiena::btrees::set_garbage: err: src or dst NULL");
	             return -1;
        }

        if( dst->garbage == NULL)
        {
                dst->garbage = src->garbage;
                src->garbage = dst;
                return 0;
        }
        HIERR("hiena::btrees::set_garbage: dst->garbage != NULL.  can not set.");

        return -1;
}

static bnode_t *add_to_upper(bnode_t *node, bnode_t *upper_n)
{
        /* # NUM_KEYS, EMPTY */
        /* this expects 'node' to have only its first key set
           and will merge node into upper_n.
           it expects upper_n has already been split_if_full
           so it returns an error if it can't find a free key element.
           it destroys 'node' on success
           -- and so expects node is NOT linked into the garbage chain. */

        /* return NULL on failure, upper_n on success */
        if(node == NULL || upper_n == NULL)
	{
		HIERR("add_to_upper: node or upper_n NULL.");

		return NULL;
    	}

	if(node->key[0] == EMPTY || node->key[1] != EMPTY)
	{
		HIERR("add_to_upper: node->key[0] == EMPTY || node->key[1] != EMPTY");
		return NULL;
	}

	bnode_t *swap_n = bnode_new( NULL );
	int i, ni, ui, si;

	i  =  0;
	ni =  0;
	ui =  0;
	si = -1;

    	for(;  i<NUM_KEYS;  i++ )
	{
		if(node->key[ni] != EMPTY)
		{
			if(upper_n->key[ui] != EMPTY)
			{
				if(node->key[ni] < upper_n->key[ui])
				{
					swap_n->key [i] = node->key [0];
					swap_n->val [i] = node->val [0];
					swap_n->link[i] = node->link[0];
					swap_n->link[i+1] = node->link[1];
					/* defer copying node->link[ni+1]; */
					si = i;	/* record where key was inserted */
					ni++;
				} else {
					swap_n->key[i]  = upper_n->key[ui];
					swap_n->val[i]  = upper_n->val[ui];
					swap_n->link[i] = upper_n->link[ui];
					/* defer copying upper_n->link[ui+1]; */
					ui++;
				}
			}  else {
				swap_n->key [i] = node->key [0];
				swap_n->val [i] = node->val [0];
				swap_n->link[i] = node->link[0];
				/* defer copying node->link[ni+1]; */
				/* unless last key */
				si = i;		/* record where key was inserted */
				i++;
				break;
			}
		} else {
			swap_n->key [i] = upper_n->key [ui];
			swap_n->val [i] = upper_n->val [ui];
			swap_n->link[i] = upper_n->link[ui];
			/* defer copying upper_n->link[ui+1]; */
			ui++;
		}
	}
	/* finish deferred actions */
	swap_n->link[i]  = upper_n->link[ui];
	swap_n->link[si+1] = node->link[1];

	/* expect that key was successfully set, but if it wasn't return error */
	if(si == -1)
	{
		bnode_cleanup(swap_n);	/* this is why we deferred setting swap_n's garbage; */
		return NULL;
	}

	/* COPY SWAP TO UPPER_N */
	for(i=0; i<NUM_KEYS; i++) {
		upper_n->key [i] = swap_n->key [i];
		upper_n->val [i] = swap_n->val [i];
		upper_n->link[i] = swap_n->link[i];
	}
	upper_n->link[i] = swap_n->link[i];	/* copy last link */


	/* CLEANUP UNUSED TEMP NODES */
	bnode_cleanup(node);	/* we deferred new_upper_n's garbg in split_if_full */
	bnode_cleanup(swap_n);


	return upper_n;
}

static bnode_t *split_if_full (bnode_t *node) { /* #define NUM_KEYS, EMPTY */
    						/* == node (if not split)
						    | new_upper_n (if split)
						    | NULL on err
						 */

    if(node == NULL) {			/* return NULL on err */
	return NULL;
    }
    if(node->key[NUM_KEYS-1] == EMPTY) {/* return same node, node isn't full */
	return node;
    }


    bnode_t *new_upper_n= bnode_new(NULL);	/* defer garbage collection
						   this node will be destroyed 
						   by add_to_upper,
						   or we must set garbage later */
    bnode_t *split_n    = bnode_new(node);

    int mi              = NUM_KEYS/2+2;
    new_upper_n->key[0] = node->key[mi];
    new_upper_n->val[0] = node->val[mi];
    node->key[mi]       = EMPTY;
    node->val[mi]       = NULL;
    new_upper_n->link[0]= node;
    new_upper_n->link[1]= split_n;

    int i, si;
    for(i = mi+1, si = 0; i < NUM_KEYS; i++, si++) {
	split_n->key [si] = node->key [i];
	split_n->val [si] = node->val [i];
	split_n->link[si] = node->link[i];
	node->key [i]     = EMPTY;
	node->val [i]     = NULL;
	node->link[i]     = EMPTY;
    }
    split_n->link[si]   = node->link[i];
    node->link[i]         = EMPTY; /* cleanup last link in node */

    return new_upper_n;
}

/**
 * @n     node to search
 * @k     desired key
 * @kres  found key (result)
 */
void
*bnode_value_at_key_or_nearest_lesser( bnode_t *n, bkey_t k, bkey_t *kres )
{
        if( n == NULL )
        {
                HIERR("bnode_value_at_key_or_nearest_lesser: err: n == NULL");
                return NULL;
        }

        int i;

recurse:
        for(i = 0;
            i < NUM_KEYS
            && n->key[i] < k;
            i++);

        if( n->key[i] == k )
        {
                if(kres != NULL)
                  *kres = n->key[i];
                return n->val[i];
        }

        if( n->link[i] != NULL )
        {
                n = n->link[i];
                goto recurse;
        }

        if( i > 0 )
        {
                if(kres != NULL)
                  *kres = n->key[i];
                return n->val[i-1];
        }
        
        HIERR( "bnode_value_at_key_or_nearest_lesser: err: i <= 0" );

        return NULL;
}



bnode_t *bnode_insert_kv( bnode_t *n, bkey_t key, void *val )
{
        if(n == NULL)
        {
                HIERR("btrees: bnode_insert_kv: input n NULL");
                return NULL;
        }
        int i;
        void *next_key, *next_val;

        /* RIPPLE INSERT */
                for(i=0; i<NUM_KEYS; i++)
                {
                        if(n->key[i] == EMPTY)
                        {
                                n->key[i] = key;
                                n->val[i] = val;
               
                                break;
	                     }

                        if(key < n->key[i])
                        {
                                next_key = n->key[i];
                                next_val = n->val[i];
                                n->key[i] = key;
                                n->val[i] = val;
                                key = next_key;
                                val = next_val;

                                continue;
                        }

                        if(key > n->key[i])
                        {
                                continue;
                        }

                        if(key == n->key[i])
                        {
                                i++;

                                continue;
                        }
                }
                return n;
}

bnode_t *bnode_add( bnode_t *n, bkey_t key, void *val )
{
        static int counter;
        bkey_t next_key;
        void *next_val;
        int i;

        if( n == NULL
         || key == EMPTY)
                return NULL;

        next_key = EMPTY;
        next_val = NULL;


        /* LEAF */

        if(n->link[0] == NULL)
        {
                return bnode_insert_kv( n, key, val );

        } else {

                /* BRANCH */

                for(i=0; i<NUM_KEYS; i++)
                {
                        if(key < n->key[i])
                        {
                                return n->link[i];
                        }

                        if(key == n->key[i])
                        {
                                /* key already exists */
		                         return n;
                        }

                        /* treat as success   */

                        if(n->key[i] == EMPTY)
                        {
                                return n->link[i];
                        }
                }
                return n->link[i];
        }
}


/* bnode_tree_add should be called like
 * "bnode_t *root_n = bnode_tree_add(root_n, key, val);"
 */

bnode_t *bnode_tree_add(bnode_t *root_n, bkey_t key, void *v )
{
        if(root_n == NULL || key == EMPTY)
        {
                return root_n;
        }

        bnode_t *cur_n    = root_n;
        bnode_t *upper_n  = NULL;
        bnode_t *res_n    = NULL;
        bnode_t *cur_root = root_n;

do_tree_add:
        res_n = split_if_full( cur_n );


        /* ERROR ON SPLIT */

        if( res_n == NULL )
        {
                HIERR("hiena::btrees::bnode_tree_add: ERROR ON SPLIT\n");

                return cur_root;
        }


        /* SPLIT */

        if( res_n != cur_n )
        {
                if(upper_n == NULL)
                {

                        cur_root = res_n;

                        set_garbage ( cur_root, root_n );

                        cur_n = cur_root;

			goto do_tree_add;

	        } else {
                        res_n = add_to_upper( res_n, upper_n );

                        if( res_n != upper_n )
                        {
                                HIERR("bnode_tree_add: adding to upper failed.");
                                return NULL;
                        } else {
                                upper_n = res_n;
                                cur_n   = upper_n;
                        }
	           
                }
	}

	/* NOT SPLIT */

	if( res_n == cur_n )
        {
	        res_n = bnode_add( cur_n, key, v );
	        if( res_n == NULL )
		{
			HIERR("bnode_tree_add: notice: identical key exists.");
		        return cur_root;
	        }
	        if(res_n == cur_n)
		{ /* cur_n is leaf, successful add */
		        return cur_root; /* success, return value of cur root */
	        } else {		 /* res_n is link, setup recursion: */
		        upper_n = cur_n; /* current node becomes upper node */
		        cur_n   = res_n; /* link becomes current node */
	        }
	}

	/* expect always to evaluate true */
        if(cur_n != NULL)
	        goto do_tree_add; 

	HIERR("hiena::btrees::bnode_tree_add err: unexpected cur_n == NULL at end of function");
        return root_n;
}



