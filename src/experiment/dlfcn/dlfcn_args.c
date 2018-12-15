#include <stdio.h>
#include <dlfcn.h>


int main( int argc, char *argv[] )
{
        printf("RTLD_LAZY == %d\n", RTLD_LAZY);
        printf("RTLD_NOW == %d\n", RTLD_NOW);
        printf("RTLD_GLOBAL == %d\n", RTLD_GLOBAL);
        printf("RTLD_LOCAL == %d\n", RTLD_LOCAL);
        printf("RTLD_LAZY | RTLD_GLOBAL == %d\n", RTLD_LAZY | RTLD_GLOBAL);
        printf("RTLD_LAZY | RTLD_LOCAL == %d\n", RTLD_LAZY | RTLD_LOCAL);
        printf("RTLD_NOW | RTLD_GLOBAL == %d\n", RTLD_NOW | RTLD_GLOBAL);

        printf("(RTLD_LAZY | RTLD_GLOBAL) & 255 == %d\n", (RTLD_LAZY | RTLD_GLOBAL) & 255);

        printf("(RTLD_NOW | RTLD_GLOBAL) & 255 == %d\n", (RTLD_NOW | RTLD_GLOBAL) & 255);

        printf("1 | 2 == %d\n", 1 | 2);
        printf("1 | 255 == %d\n", 1 | 255);
        printf("1 | 256 | 512 == %d\n", 1 | 256 | 512);
        printf("768^512 == %d\n", 768^512);
        printf("sizeof(int) == %d\n", sizeof(int));


        return 0;
}