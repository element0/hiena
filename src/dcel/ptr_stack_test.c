#include <stdio.h>
#include <stdlib.h>
#include "ptr_stack.h"

int main()
{
        ptr_stack_t p = ptr_stack_new();

        void *test;
        int i;

        for ( i = 0; i < 10; i++ )
        {
                test = malloc(sizeof(char)*8);
                ptr_stack_push(p, test);
        }

        test = ptr_stack_top(p);
        printf("top:%lu\n",(unsigned long)test);
        if(test != NULL)
               free(p);

        while( i-- > 0 )
        {
                test = ptr_stack_pop(p);
                printf("%d) top:%lu\n",i,(unsigned long)test);
                if(test != NULL)
                        free(p);
        }

        ptr_stack_cleanup(p);

        return 0;
}