
#include <stdlib.h>
#include <dlfcn.h>
#include "cosmos_dlfcn.h"


int main( int argc, char *argv[] )
{
        void *dl;
        int (*fn)(int x, int y);
        int ret;

        dl = dlopen("../lib/dummy.so", RTLD_NOW | RTLD_GLOBAL );

        fn = dlsym(dl, "dummyfn");

        ret = fn(3,5);

        dlclose(dl);

        dl = cosmos_dlopen(NULL, NULL, "../lib/dummy.so", COSMOS_RTLD_NOW | COSMOS_RTLD_LOCAL | COSMOS_RTLD_NOVM );



        fn = cosmos_dlsym(dl, "dummyfn");

        
        ret = fn(3,5);

        cosmos_dlclose(dl);

        return ret;
}