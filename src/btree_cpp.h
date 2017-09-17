

typedef struct hbtree btree_t;
typedef void* bkey_t;


btree_t *btree_new();


void *btree_get(btree_t *, void *key);

void *btree_put(btree_t *, void *key, void *val );

void btree_print(btree_t *);

int btree_cleanup( btree_t * );


void
*btree_value_at_key_or_nearest_lesser( _t *n, bkey_t k, bkey_t *kres );

