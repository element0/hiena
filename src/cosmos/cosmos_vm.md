



cosmos_vm
---------



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
    cosmos_vmd.h
    cosmos_vmd.o
    cosmos_vm_NAME.c




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
      load
      symlink
      call
      exec



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


