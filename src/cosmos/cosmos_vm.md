

cosmos_vm
---------

a daemon service with socket io using an rpc message protocol and encapsulating a code execution runtime. each vm has a unique profile which defines a target architecture, language and calling convention.

  examples:
  - c fn runner
  - exec runner
  - script runner

an executable or library has a requirements profile which is matched with a vm profile.

all vm's appear local but may be remote.

the interface to all vm's is the same from libcosmos. the args for a unique vm call are marshalled by a idl template provided by the vm.


rpc argument translation
------------------------

the client generates an interface definition string in a particular language of the lib or executable opened via cosmos_dlopen. it transmits through client's cosmos_dlsym call.

   dlsym( idl_str );

the vm gets the idl_str via a message and compiles it into a generic binary stack frame idl. the idl describes the grammar of the rpc call's stack frame in a generic format.

   return idl;

the client uses the idl to marshall the stack frame into a message and send to the vm.

   msg =
   marshall(idl, client_stack_frame);

the vm uses the same idl to unmarshall the stack frame and uses a call generator to produce a call using the native calling convention.

   vm_call_frame =
   unmarshall(idl, msg);

   generate_call(vm_call_frame);

this way, the vm native function is unaware of the interface translation.



designing a vm
--------------

a vm must parse a function prototype and generate a variables template. the variables template is used to marshall and unmarshall the arguments.

a vm must locate and load a library, fork an executable or otherwise load and run code. it keeps a table of id's, runables and variable templates.

a vm responds to a vocabulary of messages.

a vm_call message passes an id and marshalled arguments. the vm unmarshalls the args and generates a function call. the call is generated via a piece of low-level code 



vm lifecycle and use
--------------------

cosmos_dl 

cosmos_dlopen identifies a target to open. it identifies a vm platform that will run the target. launches the vm as necessary. connects the vm to a dl object. asks the vm to open the target. receives a token to the open object from the vm and stores in the dl object.

cosmos_dlsym asks the vm to provide a token based on a function prototype string. it receives a token representing the function and marshalling directions. it initializes a cosmos_vfn() function wrapper with the token, prototype string, marshalling directions and dl object. it returns a unique c function pointer to the cosmos_vfn() function.

the cosmos_vfn function uses cosmos_vm_call with the arguments marshalling directions, args array, vm, function token and execution context. it returns the return value.

cosmos_vm_call marshalls the args and execution context; asks the vm to call the function given the token and the marshalled elements. it receives a result buffer and unmarshalls the result into any relevant argument pointers and return value.





socket interface
----------------

the cosmosdb manages socket locations and passes file descriptors to the vm client process.

default socket locations are defined by the cosmos config system, including cosmosdb's socket.




api interface
-------------

cosmos_vm_open()
cosmos_vm_close()

cosmos_rp_call()

cosmos_dlopen()
cosmos_dlsym()
cosmos_dlclose()

cosmos_exec()


cosmos dl open,sym,close and exec are implemented as rpc's via cosmos_rp_call.

cosmos_rp_call is also used to call cosmosd.

cosmos_vm_open is a front end for the cosmosd. cosmosd determines which host the vm should run on and runs it; returns a handle.

cosmos_exec uses cosmosd to identify host and get a connection. then, cosmos_exec contacts the host via cosmos_rp_call, captures the return and closes/releases the connection.



architecture
------------

client interface
    cosmos_vm.h
    cosmos_vm.o

socket
    cosmos_rpc.h
    cosmos_rpc.o
    cosmos_socket.h
    cosmos_socket.o

daemon
    cosmos_vm_core.c
    cosmos_vm_core.h
    libcosmos_vm_core.a
    cosmos_vm_SOMENAME.c




structure
---------

  main loop
    check socket
    accept new connection
    check connections
    accept request
    process request
    close connection


  process request
    switch cmd
      open
      symlink
      call
      exec
      close



hostfn vm prototype
-------------------

cmds
      open
      sym
      call
      exec
      close

open
      call dlopen()

sym
      call dlsym()


