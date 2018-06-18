



cosmos_exec
-----------

cosmos exec takes an access frame to an executible.

three types of executible:

- non-exec
- internal
- external

the type is flagged in the access frame. 


cosmos exec vs hiena_scannerop_parse
------------------------------------

cosmos_exec() treats all its function objects as main() style functions or cli style processes.

writing a function for cosmos_exec() to execute is merely a matter of designing a main() style function.

hiena_scannerop_parse() works with a single input object, the Hiena Scanner Payload.  This object contains a bunch of useful values, like access frames and the cosmos_db.

naturally, both API have a different area they are trying to encapsulate for the end user.

the cosmos_exec_mapfn() convenience function translates between API.





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

