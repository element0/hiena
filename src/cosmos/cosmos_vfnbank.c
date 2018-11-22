#include <stdarg.h>
#include <stdint.h>
#include "../hierr.h"


/* virtual function wrappers,
   go into a dylib with static support functions */



const int vfncount = 1;


intptr_t cosmos_vfn0001(uintptr_t arg1, ...)
{
    static int cosmos_vfn_init_status = -1;
    int i;
    va_list ap;

    /****************************/

    /* init args:
     * these are expected on init.
     * arg1, arg2
     */

    static cosmos_dl_hdl *cosmosdl;
    char *fndefstr;


    /* cosmosdl has refs to cosmosdb
     * and the virtual machine which
     * will exec this func.
     */

    /****************************/

    /* extrapolated init values: */

    static cosmos *cosmosdb;
    void *vm;
    static string_id_t fnid;
    static int argc;
    void **argv;
    intptr_t retval;


    /* run time args
     */

    cosmos_id_t context;


    /*****************************
    function initializer
    
    */

    if(cosmos_vfn_init_status == -1)
    {
        if(arg1 == 0)
        {
            HIERR("cosmos_vfn0001: err: can't init: arg1 0");
            return NULL;
        }

        cosmosdl = arg1;

        va_start(ap, 1);

        vfndefstr = va_arg(ap, char *);

        va_end(ap);

        
        cosmos_vfn_init_status = 1;


        return cosmos_vfn0001;
    }




    /*****************************
    function runner
    
    */


    er = cosmos_vm_call( cosmosdb, vm, vfnid, context, argc, argv, &retval );


    return retval;





    /* WIP */


    if(cosmos_vfn_init_status > 0)
    {
        /* demo morphism: calc */

        /* include first arg */
        res += init;
        
        va_start(ap, argc);
        for(i = 0; i < (argc-1); i++)
        {
            cur = va_arg(ap, int);
            res += cur;
        }
        va_end(ap);

        // printf("result: %d\n", res);

        return res;
    }
    

    return NULL;
}

