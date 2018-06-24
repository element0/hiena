



cosmos_exec
-----------

cosmos exec takes an access frame to an executible.

three types of executible:

- none
- built-in
- module-supported

the type is flagged in the access frame. 



chicken and egg with built-ins
------------------------------

an example of how a module supported executible is run via built-ins.


  aframe_id: "pathto/somemod/mapfn"
  par: "pathto/somemod"
  exectype: module-supported
  module_id: "dlsym"
  addr: "mapfn"
  value: (will become fnptr)


to run mapfn, we have to: 1) run the open method from its module.  2) use the result as a function pointer and run it.  3) run the close method from its module.


  aframe_id: "pathto/dlsym/open"
  exectype: built-in
  value: (fnptr) dlsym_open

  aframe_id: "pathto/dlsym/close"
  exectype: built-in
  value: (fnptr) dlsym_close

  
  void *dlsym_open(addr,par)
  {
      open_parent(par);
      ret=dlsym(par, addr);
  }

  void dlsym_close(par)
  {
      close_parent(par);
  }



these methods call methods from the parent "somemod":

  aframe_id: "pathto/somemod"
  exectype: none
  module_id: "dlib"
  addr: "filepathto/somemod"
  value: (will become ptr to dl)

  aframe_id: "pathto/dlib/open"
  exectype: built-in
  value: (fnptr) dlib_open

  aframe_id: "pathto/dlib/close"
  exectype: built-in
  value: (fnptr) dlib_close

  void *dlib_open(addr)
  {
      if opencount opencount++;
      else if res = dlopen(addr)
          opencount++;
      return res;
  }

  
  void dlib_close(ptr)
  {
      
      if --opencount = 0
          dlclose(ptr);

  }


sandboxing - v2 feature
-----------------------

before a function ptr is run, fork and run to ensure segfaults and crashing modules do not bring down cosmos.



algo
----

is the aframe executable?
  is it internal?
    setup context frame
      args, env, stdio, etc.
    open aframe
    read function ptr value
    fork and run function
    close aframe
  is it external?
    setup context sandbox
      args, env, stdio, etc.
    fork executible, capture output
    

    

prepare apropriate exec helper


cosmos_exec_mapfn
   switch executible type
     1: cosmos_exec_mapfn_internal
     2: cosmos_exec_mapfn_external


cosmos_exec_mapfn_internal
   prep args for 

cosmos_exec_mapfn_external




cosmos exec vs hiena_scannerop_parse
------------------------------------

cosmos_exec() treats all its function objects as main() style functions or cli style processes.

writing a function for cosmos_exec() to execute is merely a matter of designing a main() style function.

hiena_scannerop_parse() works with a single input object, the Hiena Scanner Payload.  This object contains a bunch of useful values, like access frames and the cosmos_db.

naturally, both API have a different area they are trying to encapsulate for the end user.

the cosmos_exec_mapfn() convenience function translates between API.






