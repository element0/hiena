#ifndef HIENA_BTREE_CPP_H
#define HIENA_BTREE_CPP_H


#include <stdint.h>


typedef struct hbtree btree_t;
typedef struct hbtree_curs btree_curs;
typedef uintptr_t bkey_t;
typedef uintptr_t bval_t;
#define BVAL_NULL 0


btree_t *btree_new();

bval_t btree_get(btree_t *, bkey_t key);

void *btree_put(btree_t *, bkey_t key, bval_t val );

void btree_print(btree_t *);

int btree_cleanup(btree_t *);

btree_curs *btree_get_curs(btree_t *);

void btree_curs_cleanup(btree_curs *);

void *btree_curs_incr(btree_curs *);

bval_t btree_curs_value(btree_curs *);


bval_t btree_first_value( btree_t * );

bval_t
btree_value_at_key_or_nearest_lesser(btree_t *, bkey_t k, bkey_t *kres );

#endif /* !HIENA_BTREE_CPP_H */

