



#include <stdio.h>
#include "btrees.h"

int btree_test_lt( void *k, void *k2 )
{
        return k < k2;
}

void main(int argc, char *argv[])
{
        btree_t *bt;
        int num_inserts;
	long int i, rnd;

        if(argc == 2)
                num_inserts = atoi(argv[1]);
        else
                num_inserts = MAX_INSERTS;


        bt = btree_new( btree_test_lt );

        for(i=0;i<num_inserts;i++)
        {
                /* btree_put(bt, (ino_t)rand(), NULL); */
		rnd = rand();
                btree_put(bt, (void *)i, (void *)rnd);

                if(bt->root == NULL)
                {
                        fprintf(stderr, "bt->root became NULL on %ld\n",i);
	                     break;
                }
        }


        fprintf(stderr, "original root: %p\n", bt->garb);
        fprintf(stderr, "current root:  %p\n", bt->root);
        printf("digraph \"b-tree test\" {\n");
        fflush(stdout);
        btree_print( bt );
        printf("}\n");
        fflush(stdout);
        fflush(stderr);


        btree_cleanup( bt );
}
