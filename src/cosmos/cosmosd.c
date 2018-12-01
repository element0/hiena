


#include "cosmos_server_core.h"
#include "cosmos_msg.h"



/*
  cosmos_server_core provides a server loop, connections and memory management.

  this file implements functions which are called from the server core. their names are declared in the cosmos_server_core interface.
 */




struct cosmosd {
        void *temp;
        struct cosmos_db *db;
};




void *server_module_init( int argc, char *argv[] )
{
        return NULL;
}


int server_module_cleanup( void *d )
{
        return NULL;
}


struct cosmos_msg *server_module_handle_msg( void *d, struct cosmos_msg *msg )
{
        return NULL;
}


