/* cosmos_vm_localhost runs locally installed libs and executables. */


/*
   cosmos_vm_core configures the cosmos_server_core and provides a main function to create a standalone daemon.

   this file implements interface functions which are declared in cosmos_server_module.h and used in the cosmos_vm_core and cosmos_server_core.

 */


/* cosmos_server_msg provides a "flatbuffers" message format.
 */
#include "cosmos_server_msg.h"




void *server_module_init( int argc, char *argv[] )
{
        return NULL;
}


int server_module_cleanup( void *d )
{
        return 0;
}


struct cosmos_msg *server_module_handle_msg( void *d, struct cosmos_msg *msg )
{
        return NULL;
}



