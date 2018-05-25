
#include <dlfcn.h>
#include "../../hierr.h"


void main(int argc, char *argv[])
{
        void *dl;
        struct cosmos_module *mod;
        char *fn = "./file.so";
        char *modsym = "cosmos_module";

        if(argc == 2)
        {
                fn = argv[1];
        }

        dl = dlopen(fn, RTLD_LAZY);

        if( dl == NULL )
        {
                HIERR("test_file_mod: dl NULL");
                return;
        }

        mod = dlsym(dl, modsym);

        if( mod == NULL )
        {
                HIERR("test_file_mod: mod NULL");
                return;
        }


        dlclose(dl);

        
}