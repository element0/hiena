#include "cpp-btree/btree_map.h"





int main( int argc, char *argv[] )
{
        typedef btree::btree_map<int,int> MyMap;

        MyMap *obj_map = new MyMap;

        const int maxi = 10;
        int i, id, obj;
        MyMap::iterator lookup;
        
        for (i=0; i<maxi; i++)
        {
                lookup = obj_map->find(i);
                if (lookup != obj_map->end())
                {
                        // "id" already exists.
                        continue;
                }
                obj = i*100;
                obj_map->insert(std::make_pair(i, obj));
        }

        for(lookup = obj_map->begin(); lookup != obj_map->end(); lookup++)
        {
                std::cout<<lookup->first<<":"<<lookup->second<<"\n";
        }

        delete obj_map;

        return 0;
}