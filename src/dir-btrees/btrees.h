#ifndef HIENA_BTREES_H
#define HIENA_BTREES_H

#include <sys/types.h>

#define BTREE_CPP
#ifdef BTREE_CPP

#include "btree_cpp.h"

#endif
#ifndef BTREE_CPP

#define NUM_KEYS  5
#define ROOTKEY 1
#define MAX_INSERTS 20


typedef void* bkey_t;
#define EMPTY NULL

#ifdef BTREE_DBUG
#define BTREE_DBUG_OUT( fstr, str ) fprintf(stderr, fstr, str)
#endif

/* implement your own garbage collector for 'val' */
typedef struct bnode bnode_t;
struct bnode
{
        bkey_t key[NUM_KEYS];

        void *val[NUM_KEYS];

        bnode_t *link[NUM_KEYS+1];

        bnode_t *garbage;
};

bnode_t *bnode_new ( bnode_t *garbage );

void bnode_cleanup(bnode_t *node);

void bnode_init_root(bnode_t *root_n);

bnode_t *bnode_add(bnode_t *n, bkey_t key, void *val);

bnode_t *bnode_tree_add(bnode_t *root_n, bkey_t key, void *v );

void bnode_tree_cleanup(bnode_t *root_n);

bnode_t *btree_add(bnode_t *root_n, bkey_t key, void *val);


typedef struct hiena_btree btree_t;
struct hiena_btree
{
        bnode_t *root;
        bnode_t *garb;

        /* key comparison op */
        int (*lt)(void *, void *);
};

btree_t *btree_new();


void *btree_get(btree_t *, bkey_t key);

void *btree_put(btree_t *, bkey_t key, void *val );

void btree_print(btree_t *);

int btree_cleanup(btree_t *);

void
*btree_value_at_key_or_nearest_lesser(btree_t *, bkey_t k, bkey_t *kres );


typedef struct hiena_btree_curs btree_curs_t;
struct hiena_btree_curs
{
        bnode_t bnode;
        void *key;
        void *val;
};

btree_curs_t
*btree_curs_at_key_or_nearest_lesser( bnode_t *n, bkey_t k, bkey_t *kres );

btree_curs_t
*btree_curs_seek_key_or_nearest_lesser( btree_curs_t *, bkey_t k );

#endif /* !BTREE_CPP */


#endif /*! HIENA_BTREES_H */
