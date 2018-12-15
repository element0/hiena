#include <dlfcn.h>
#include <stdlib.h>

#include "cosmos_dlfcn.h"
#include "../hierr.h"


static uintptr_t cosmos_dlopen_native(const char *fpath, int flags)
{
        uintptr_t dl;
        int32_t flags_native;




        if((flags & 255) == 1)
                flags_native = RTLD_LAZY;


        if((flags & 255) == 2)
                flags_native = RTLD_NOW;


        if((flags & COSMOS_RTLD_GLOBAL) == COSMOS_RTLD_GLOBAL)
                flags_native = flags_native | RTLD_GLOBAL;


        if((flags & COSMOS_RTLD_LOCAL) == COSMOS_RTLD_LOCAL)
                flags_native = flags_native | RTLD_LOCAL;


        dl = (uintptr_t)dlopen(fpath, flags_native);

        return dl;
}


static uintptr_t cosmos_dlopen_vm(struct cosmos *cm, struct access_frame *af, const char *fpath, int flags)
{
        return (uintptr_t)NULL;
}


void *cosmos_dlopen(struct cosmos *cm, struct access_frame *af, const char *fpath, int flags)
{
        struct cosmos_dl_hdl *dlh;
        uintptr_t dl;
        int32_t flag_test;


        dl = (uintptr_t)NULL;






    /* native, load into process */


        if((flags & COSMOS_RTLD_NOVM) == COSMOS_RTLD_NOVM)
        {
            dl = (uintptr_t)cosmos_dlopen_native(fpath, flags);


        }else{

    /* virtual, load into vm */

    /*  STUB */

                dl = (uintptr_t)NULL;
                HIERR("cosmos_dlopen_vm: unimplemented.");
                return NULL;

        }

    /* cosmos dl handle */


        dlh = malloc(sizeof(*dlh));

        dlh->cosmosdb = cm;
        dlh->aframe = af;
        dlh->dl = dl;


        return (void *)dlh;
}


static int cosmos_dlclose_vm( void *dlh )
{
        /* STUB */

        return 0;
}


int cosmos_dlclose( void *dlhp )
{
        struct cosmos_dl_hdl *dlh = dlhp;
        int er = 0;

        if(dlh == NULL)
        {
                HIERR("cosmos_dlclose: dlh NULL");
                return -1;
        }

        if(dlh->vmid != 0)
        {
                er = cosmos_dlclose_vm( dlh );


        }
        if(dlh->dl != (uintptr_t)NULL
           && dlh->vmid == 0)
        {
                 dlclose((void *)(dlh->dl));


        }

        free(dlh);

        return 0;
}