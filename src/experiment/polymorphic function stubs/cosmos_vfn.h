#ifndef _COSMOS_VFN_H_
#define _COSMOS_VFN_H_


typedef struct rpc_instr {
        void *vm_hdl;
        char *idl;
        void *vmfn_hdl;
        void *marshal_instr;
        void *context;
        void *ret;
}rpc_instr_t;


#endif /* !_COSMOS_VFN_H_ */
