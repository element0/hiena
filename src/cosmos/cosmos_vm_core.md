
cosmos vm core
--------------

library component of a vm.  provides common actions such as sockets, client connections, cosmosdb connection.

uses cosmos_server_core

cosmos_vm_core provides:

   main

to implement a vm, you need to implement the following interface:

   libopen
   libsym
   libclose
   exec
   vm


include "cosmos_vm_core.h", compile your object file and link with cosmos_vm_core.o or libcosmos.



socket path
-----------

determined by cosmosd.

the socket path is passed to the vm core as a command line option.