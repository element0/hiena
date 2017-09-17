#include "cpp-btree/btree_map.h"


namespace btree_cpp {

typedef void* bkey_t;
typedef btree::btree_map<bkey_t,void *> hbtree;



extern "C" {
#include <stdlib.h>

hbtree *btree_new()
{
        return new hbtree;
}
 
int btree_cleanup( hbtree *bt )
{
        if( bt == NULL )
                return -1;

        delete bt;
        return 0;
}


void *btree_get(hbtree *bt, bkey_t key)
{
        if( bt == NULL )
                return NULL;

        hbtree::iterator it;
 
        it = bt->find(key);
        if( it == bt->end() )
        {
                return NULL;
        }
        return it->second;
}

void *btree_put(hbtree *bt, bkey_t key, void *val )
{
        if( bt == NULL )
                return NULL;

        std::pair res;

        res = bt->insert(std::make_pair(key,val));

        if( res->second == FALSE )
        {
                return NULL;
        }
        return (void *)res->first;
}

void btree_print(hbtree *bt)
{
        hbtree::iterator it;
        for(it = bt->begin();
            it != bt->end();
            it++;)
        {
                std::cout << it->first << ":" << (long unsigned int)(it->second) << "\n";
        }
}

// purpose of btree_value_at_key_or_nearestreturn_lesser is to discover a fragment that contains the key within its bounds.  considering the keys are the start boundary.
// the cpp STL map interface (used by cpp_btree) provides a 'lower_bound()' which finds iterator at key or nearest greater.
// ergo, we could use lower_bound() on a map of end bounds.

void
*btree_value_at_key_or_nearest_lesser( hbtree *bt, bkey_t k, bkey_t *kres )
{
        if( bt == NULL )
                return NULL;

        hbtree::iterator it;
        
        it = bt->lower_bound;

        if( it->first != k )
        {
            if( it == bt->begin() )
                return NULL
            it = --it;
        }

        return it->first;
}

void
*btree_value_at_key_or_nearest_greater( _t *n, bkey_t k, bkey_t *kres )
{
        return NULL;
}


}