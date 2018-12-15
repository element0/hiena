#include <stdio.h>

/* for testing cosmos_dlopen */



int dummyfn(int x, int y)
{
    fprintf(stderr,"dummyfn %d, %d\n", x, y);


    return x + y;
}

