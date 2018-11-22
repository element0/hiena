#ifndef _COSMOS_VM_CORE_H_
#define _COSMOS_VM_CORE_H_


/** a reusable vm core.
 */


typedef struct cosmos_conn {

}cosmos_conn_t;




struct cosmos_vm_core {

        /**
         the functions which open, link and exec are provided via a struct of function pointers 'struct cosmos_vm_ops'.
         */

        struct cosmos_vm_ops *cosmos_vm_ops;


        /** open libraries
         */

        int open_libs_size;
        int open_libs_count;
        void *cosmos_vm_open_libs[];


        /** open functions:
         maps between fnid and fnptr
         */

        int open_fns_size;
        int open_fns_count;
        uintptr_t *cosmos_vm_open_fns[];



        /** socket
         */

	     struct sockaddr_un sa;


        /** cosmosdb connections:
          allows multiple db servers
          in case that is useful.
         */

        cosmos_conn_t *cmdb_con[];



        /** client connections
         */

        cosmos_conn_t *client[];

};


#endif /* ! _COSMOS_VM_CORE_H_ */
