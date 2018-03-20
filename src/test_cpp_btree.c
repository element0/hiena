#include <stdio.h>
#include "btree_cpp.h"


int main( int argc, char *argv[] )
{
        btree_t *obj_map = btree_new();

        const bkey_t maxi = 10;
        bkey_t k, v, kp;
        unsigned long i,j;
        btree_curs *curs;
        
        for (i=0; i<maxi; i++)
        {
                k = (void *)i;
                j = i*100;
                v = (void *)j;
            if(i!=5)
            {
                btree_put(obj_map,k,v);
            }
        }
        for (i=0; i<maxi; i++)
        {
                k = (void *)i;
                v = btree_get(obj_map,k);
                printf("get %lu:%lu\n",(unsigned long)k,(unsigned long)v);
        }

        btree_print(obj_map);

        j = 5;
        k = (void *)j;
        v = btree_value_at_key_or_nearest_lesser(obj_map, k, &kp );

        printf("btree_value_at_key_or_nearest_lesser 5:%lu\n",(unsigned long)v);


        curs = btree_get_curs(obj_map);


        btree_cleanup(obj_map);

        return 0;
}