#include "cosmos_vfn.h"
#include "../hierr.h"


/* virtual function wrappers,
   go into a dylib with static support functions */



const int vfncount = 1;


void *vfn0001(rpc_instr_t *rpc, ...)
{
    static rpc_instr_t *rpc_instr = NULL;

        
    if(rpc_instr == NULL)
    {
        if(rpc == NULL)
        {
            HIERR("vfn0001: err: can't init: rpc AND rpc_instr input NULL");
            return NULL;
        }

        return vfn001;
    }
}
