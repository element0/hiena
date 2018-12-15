




VFCallFrame
------------

VFCallFrame carries stack frame and context to the VM to execute a function or executable. The VM uses the info to duplicate the calling environment.

VFCallFrame also carries idl information returned from cosmos_dlsym(): argv with sizes but no bodies, fnid with full value. this idl info is used by the caller to build a calling VFCallFrame.

VFCallFrame carries VM control calls like, cosmos_dlopen() and cosmos_dlsym(). The control functions are standardized and pre-numbered and their idl's are included at compile time.

VFCallFrame carries return values and modified environment.


stack frame representation
--------------------------

as an example, the c language passes values and pointers in registers and stack. pointers typically point to an address in the heap.

CLI args are an array of pointers to strings.

http post args and envars are key-value string pairs.

a VFCallFrame should be generic enough to work as an FFI between calling conventions and detailed enough to be disambiguous.


shared memory delima
--------------------

unlike an http request, a transparent RPC cannot expect that all resources, especially in-heap objects will be available for the remote callee.

the idea is to pass needed resources within the call frame. however, a non-leaf function may trigger other functions which expect related resources to be available.

either a) limit rpc's to atomic call resources and leaf callees, or b) transfer a closed system of objects to a closed system of callees, or c) give the caller and callee interfaces to a distributed, shared memory model.

option a, atomic, is the first step.



representation
--------------

an argument can be minimally represented by

 arg
   size in bytes
   value
   ptr flag

supported by

   serialized heap space


sample structure:
 
  struct VFCallframe {
    bitflags_t ptrflag;
    sizeflags_t argsize[];
    valu_t argvalu[];
    epic_shm_t *heap;
  };

  
   
mapping memory before marshalling
---------------------------------

because cosmos_dlsym takes a function prototype string as it's input, it should be possible for the sender and receiver to map memory objects used by the function as long as the prototype uses type names in its params. both sides of the rpc would need access to the same header files.

the difficult types would be dynamic  arrays and buffers which need an associated size variable. variable associations could be embedded by using variable names or comments in the prototype string.



it is probably simpler to achieve through an object oriented language.


