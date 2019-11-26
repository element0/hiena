#include "cpp-btree/btree_map.h"
#include <stdint.h>


namespace btree_cpp {

typedef uintptr_t bkey_t;
typedef uintptr_t bval_t;
#define BVAL_NULL 0
typedef btree::btree_map<bkey_t, bval_t> hbtree;


class IterWrapper {
    public:
        hbtree *bt;
        hbtree::iterator it;
};


typedef IterWrapper hbtree_curs;


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


bval_t btree_get(hbtree *bt, bkey_t key)
{
        if( bt == NULL )
                return BVAL_NULL;

        hbtree::iterator it;
 
        it = bt->find(key);
        if( it == bt->end() )
        {
                return BVAL_NULL;
        }
        return it->second;
}

void *btree_put(hbtree *bt, bkey_t key, bval_t val)
{
        if( bt == NULL )
                return nullptr;

        std::pair<hbtree::iterator,bool> res;
        hbtree::iterator *it;

        res = bt->insert(std::make_pair(key,val));
        it = nullptr;

        if( res.second == false )
        {
                return nullptr;
        }
        it = &(res.first);

        return (void *)it;
}

void btree_print(hbtree *bt)
{
        hbtree::iterator it;
        for(it = bt->begin();
            it != bt->end();
            it++)
        {
                std::cout << it->first << ":" << (long unsigned int)(it->second) << "\n";
        }
}

hbtree_curs *btree_get_curs(hbtree *bt)
{
        hbtree_curs *curs;

        if( bt == nullptr )
        {
                printf("bt == nullptr\n");
                return NULL;
        }


        curs = new IterWrapper;
        curs->bt = bt;
        curs->it = bt->begin();

        return curs;
}



void *btree_curs_incr( hbtree_curs *curs )
{
        if( curs == nullptr )
        {
                printf("curs == nullptr\n");
                return NULL;
        }

        if( curs->bt == nullptr )
        {
                printf("curs->bt == nullptr\n");
                return NULL;
        }
        
        if( curs->it == curs->bt->end() )
        {
                printf("curs->it == curs->bt->end()\n");
                return NULL;
        }

        curs->it++;

        return curs;
}

bval_t btree_curs_value( hbtree_curs *curs )
{
        if( curs == nullptr )
        {
                printf("curs == nullptr\n");
                return BVAL_NULL;
        }

        return curs->it->second;
}


int btree_curs_cleanup( hbtree_curs *curs )
{
        if( curs == NULL )
                return -1;

        delete curs;
        return 0;
}

bval_t btree_first_value( hbtree *bt )
{
        if( bt == NULL )
                return BVAL_NULL;

        hbtree::iterator it;
        
        it = bt->begin();

        return it->second;
}

// purpose of btree_value_at_key_or_nearestreturn_lesser is to discover a fragment that contains the key within its bounds.  considering the keys are the start boundary.
// the cpp STL map interface (used by cpp_btree) provides a 'lower_bound()' which finds iterator at key or nearest greater.
// ergo, we could use lower_bound() on a map of end bounds.

bval_t btree_value_at_key_or_nearest_lesser( hbtree *bt, bkey_t k, bkey_t *kres )
{
        if( bt == NULL )
                return BVAL_NULL;

        hbtree::iterator it;
        
        it = bt->lower_bound(k);

        if( it->first != k )
        {
            if( it == bt->begin()
             || it == bt->end() )
                return BVAL_NULL;
            it = --it;
        }

        *kres = it->first;

        return it->second;
}

}   // end extern "C"

}   // end namespace
