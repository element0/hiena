#ifndef HIENA_BTREE_CPP_H
#define HIENA_BTREE_CPP_H

typedef struct hbtree btree_t;
typedef void* bkey_t;


btree_t *btree_new();

void *btree_get(btree_t *, bkey_t key);

void *btree_put(btree_t *, bkey_t key, void *val );

void btree_print(btree_t *);

int btree_cleanup(btree_t *);

void
*btree_value_at_key_or_nearest_lesser(btree_t *, bkey_t k, bkey_t *kres );

#endif /* !HIENA_BTREE_CPP_H */

