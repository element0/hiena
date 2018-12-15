#include <stdlib.h>
#include <dlfcn.h>
#include "cosmos_dlfcn.h"
#include "../hierr.h"




static void *cosmos_dlsym_vm( struct cosmos_dl_hdl *dlh, char *idlstr )
{
        return NULL;
}




void *cosmos_dlsym(struct cosmos_dl_hdl *dlhp, char *idlstr)
{
        struct cosmos_dl_hdl *dlh = (struct cosmos_dl_hdl *)dlhp;

        uintptr_t dl;
        void *fn = NULL;


        if(dlh == NULL)
        {
                HIERR("cosmos_dlsym: dlh NULL");
                return NULL;
        }

        if(idlstr == NULL)
        {
                HIERR("cosmos_dlsym: idlstr NULL");
                return NULL;
        }

        dl = dlh->dl;



    /* NO VM, relocate into process space */

        if( dlh->vmid == 0 )
        {
                fn = dlsym( (void *)dl, idlstr );

        }else{


    /* use VM and VFn */
    /* STUB */

                fn = cosmos_dlsym_vm( dlh, idlstr );

        }


        return fn;
}