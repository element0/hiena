

overview
--------

cosmos code running situations:

  - virtual functions (transparent rpc)
  - executables (transparent rpc)
  - production instructions (distributed processing)
  - modules



transparent rpc:

its objective is to make all executable resources available to all hosts.

is the foundation of all modularity in cosmos.  because the fs is shared, any modules which affect the fs must be "runnable" from any host node.

the fudge language embedded in url's is also such a case.  a url must have equal effects on all host nodes.

a dcel's production instruction is likewise required to generate the same results on all nodes.

furthermore, the presence of an executable or library within the shared file system indicates an intent to share the exe or lib.  transparent rpc makes this possible.



distributed processing:

the objective is to decrease execution burden by dividing a complex task among hosts.

dcel production instructions are one case that can take advantage of this.



transp rpc and distrib proc:

rpc is a version of distrib proc where the distribution is one machine and the burden is undivided.

the cosmos rpc interface (cosmos_exec, cosmos_dlopen, cosmos_dlsym) and the cosmos distrib proc interface are both ontop of the cosmos distrib proc implementation. (the implementation cannot use the cosmos rpc interface internally).



descriptions.

virtual functions are accessed through the cosmos transparent rpc system.

  cosmos_dlopen()
  cosmos_dlsym()

this system provides a function pointer that may be used like a local function - even if it triggers an rpc.


executables are similarly transparent.

  cosmos_exec()

this system allows a program to run an executable as if it were local - even if if runs remote.


production instructions are data structures inside a dcels which tell how to construct the domain of the cel.  they may be a simple instruction or a program of instructions.  the prod instr interpreter executes it via the rpc-distrib system.  each intruction is a grid instruction.



grid instructions
-----------------

a grid instruction is a function id with an args list and context.  the args are structured in a way that they can be factored.  if the function is factorable, it can be split and submitted to other nodes for processing.


translating into a grid instruction and rpc
---

grid_instr_t *gin = GRIDINSTR(prodinstr);

can 'gin' be factored?

what hosts can 'gin' run on?


what hosts?
gin needs a ref to a function or executable.


factorable?
the args from the referred to function should be examined for factorable components.  



can the grid be made part of the transparent rpc call?

the api is basically the same:

fn = dlsym( dlopen( libname ), fn_idl );



factorable vs. "prime" functions
--------------------------------

factorable:

transform (on a set), overlay bind, map, find


prime:

source bind




cosmos_exec
-----------

everything that can be executed through cosmos is encapsulated by the cosmos_executable type.

ie this type can encapsulate:

    - library function
    - executable
    - script/code (sh, java, etc.)


the cosmos_executable type is used to implement the module system used by fudge and provided by the .cosm object.

the lookup function is such.

because of its incapsulation effect, the executable appears as a file in the .cosm tree.

ie:

  .cosm/lib/cosmos/lookup/lookupfn



abi vs virtualization
---------------------

first we need to look at module and executable use cases:


  file://
  ssh://
  https://

these are source services.  they provide io interfaces.  if all systems have them, they benefit from direct abi.  if one or more systems don't have, they need to be virtualized.


  somedir/somefile.mapper
  somedir/somefile.transformer

  mapper
  transformer

these are fudge modules.  provide mapper and transformer interfaces. benifit from customization and extensibility.  --virtualization.


  lookup_fudge.so

the lookup engine.  this runs on all machines.  i suppose it could be virtualized.  but its speed benefits from direct abi.


  bind://
  cascade://

two sourcerers that could go either way.


using a library function call as a transformer:


  somedir/somefile.libcall

requires virtualization.


next, we need to analyze the use of functions within the modules.  can they use direct abi?


  source io interface - the module is virtualized, the functions are abi.

  mapper - module and functions may be virtualized; or module virtualized, functions abi.

  transformer - module and functions may be virtualized; or module virtualized, functions abi.

  lookup engine - the module is virtualized, the functions are abi.

  bind and cascade - the modules are virtualized, the functions are abi.

  fn call transformer - virtualized



prototype solution:  cosmos executable format (CEF)
-------------------

the CEF knows the execution profile of its payload.  it's API behaves like a shared library: you open the CEF, and symlink one of its symbols, then use the pointer as a function or struct.

  cosmos_dlopen()
  cosmos_dlsym()

in the case of a host-native library, the CEF Loader will simply act as a passthrough for dlopen and dlsym.

in the case of a shell script or CLI executable, the CEF Loader will give a virtual pointer.  the pointer will be a host-native function within the loader which translates the input and return values.

the CEF API is a front end for the virtual machines.


special denizen of cosmos:  the CEF is implemented on the "inode" level in the cosmos fs.  it does not exist in the underlying host file system.  therefor is irrelevant to the host os.  it encapsulates multiple executable types.


fail-safe code execution - vm's
-------------------------------

if a module library call crashes, it would crash cosmosd.

it is better to isolate module calls in their own process.

a virtual machine can be a daemon process.  the module call is deligated to the vm.  after the call, the vm stays running.  on a crash, the vm is restarted.



virtual machines
----------------

executables have "requirements profiles".

an installation of cosmos will have two or more native vm's providing "capability profiles".

(matching an executable to a vm is like matching MIME types to handlers, but with more variation.)

the executable will run locally by a vm if it matches.  otherwise, the executable is run by another cosmos node on the network.



there are two required vm's:


`hostfn` runs library calls natively on the host.

`netrun` encapsulates the network.  it runs the executable on another host. 


another should be present:


`hostexec` runs programs through the host exec interface; handles binaries and interpreters starting with "#!".


other vms, though not required, can be written to bypass the "hostexec" vm for more efficient interfaces (to jvm or c#, for example).



the vm socket locations are os dependent.  on linux:

  /var/run/cosmos/vm/hostfn
  /var/run/cosmos/vm/hostfn_err



vm's and hosts
--------------

not every vm can run on every host.  if an executable requires, it must be run on a different host.





meta-data in access frames
--------------------------

cosmos exec takes an access frame to an executable.

the executable's machine profile is stored in the access frame as part of the CEF.

when cosmos_exec generates a result access frame it records the vm profile and executable required to reproduce the result.



an executable's requirements profile
------------------------------------ 

between two debian instances, running the same arch type (x86_64-linux-gnu), an executable and a dynamically loaded shared lib can be compiled on one and run on both, given the presence of lib dependencies on both machines.

lib dependencies can be listed by pax-utils.deb::lddtree.  simply enough, this list can be the 'requirements profile'.


other dependencies may in fact exist.


dependencies fall into categories:

   - libs
   - file system context
   - env context
   - dev context


libs are easy to determine via 'lddtree'.

fs, env and dev can all be abstracted via the single merged file system view available in cosmos.


a call to a cosmos_dlsym'd function or to a cosmos_exec'd program will require a the 'requirements profile' plus an 'exec context' frame.  the 'exec context' contains fs, env and dev contexts which can be virtualized within the vm.


a candidate vm must match:
   - libs required
   - cosmos fs

the context frame will give access to distributed devs and fs - local or remote.



vm capabilities profile
-----------------------

a vm's caps may be numerous.

a vm validates a requirement profile.

the vm api provides a validation call.

  cosmos_vm_accepts( profile );


recursive vm's
--------------

a vm does not run vm's.  all vm's are peers through cosmosfs.




vm's and .cosms
---------------

a cosm will have a default vm profile, usually, localhost.  the default can be changed.

the .cosm files and executables are relative to a vm because of package dependencies.

using vm's and .cosm changes the concept of the PATH variable:

review: the .cosm automatically inherits from the host:

  PATH=~/bin:/usr/local/bin:/bin
  -reduces to-
  PATH=.cosm/bin


now we add vm's

  PATH={.cosm/vm/*}:

and add the default

  PATH=.cosm/default/vm:$PATH






note: vm's vs containers
------------------------

in cosmos a vm is a runtime - like a jvm or a c# runtime which runs on the localhost.  a container is a complete virtual host ie LXC





vm distribution
---------------

how does one device inherit another devices vm's?


three devices

  mac, linux, windows



cosmos keeps handles to open vm's in the cosmosdb.

it loads them from the working .cosm in the access tree.  a vm is an executable with a profile like any other.  if the vm profile matches the device native profile, it can be run.

an executable's profile is matched against the vm's in the working .cosm.


should vm's be allowed to run other  vm's?  tbd.











-old being reworked-


chicken and egg with built-ins
------------------------------

an example of how a module supported executible is run via vms.


  aframe_id: "pathto/somemod/mapfn"
  par: "pathto/somemod"
  exectype: locahostfn
  service: "dlsym"
  addr: dlibptr/"mapfn"
  value: (will become fnptr)
  vmprofile: linux-intel


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






