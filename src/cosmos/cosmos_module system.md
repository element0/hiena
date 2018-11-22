


purpose of modules
------------------

modules provide lookup functions (query services), io services, mapping services and transformation services.  these categories mirror the production function types.


module types
------------

cosmos_lookup_service:
query dcel

cosmos_io_service:
stream & dir

cosmos_mapping_service:
map io stream & dir to hiena map

cosmos_transforming_service:
use dcels & access frames to generate new dcel w new stream & dir




example
-------

cosmos_bind() links a url to an access frame.  the protocol identifies a module.

the module provides io service from the url to the domain cel (read, write, readdir)




modules re. production functions
--------------------------------






cosmos_load_mod()
-----------------

cosmos_load_mod() is used at cosmos init time to load modules and add their essential functions to the cosmos db.




module system via fudge
-----------------------

a module's funcs are avail thru fudge.

  /pathto/mod.so/func

in fudge, the path can be resolved via a PATH resolution mechanism and via aliases.  In both, a shorthand func name expands to the full pathname.

and the full pathname resolves to an access frame pointer.




prod instr to create mod paths
------------------------------

  fpath = "/pathto/mod.so"
  fnname = "func"

  dc1 = `prodi source file $fpath`
  dc2 = `prodi xform dlopen $dc1`
  dc3 = `prodi lookup $dc2 $fnname`

  s1 = `string $fpath`
  s2 = `string "$fpath/$fnname"`

  af2 = `aframe path:$s2 dcel:$dc3`
  af1 = `aframe path:$s1 dcel:$dc1 br:$af2`


modules and ipc/rpc
-------------------

there are a few questions:
- do modules need the cosmosdb?
- can modules work without it?
- which modules can work thru rpc?
- how is context transmitted to rpc?

a module can be:
- a transparent rpc dl pointer
- a list of transp rpc funcs

what a module needs:
- the caller's execution context
  - incl. fs, env, resources

an rpc may be initialized by the call's type signature, but the actual rpc needs to pass context with the call frame.

ergo there is a potential duplication of interfaces:

- cosmos module func ptrs
- rpc func ptrs
- vm local func calls, executables


the interfaces serve multiple purposes

- cosmos module func ptrs

are to be called from within cosmos in a file system/ db context. they implement search/retrieval within dcels.

for example, a vfn is called to open a file handle. in the case of a relative pathname, the process's CWD should be available to the rpc.




- rpc func ptrs

are intended to extend a remote API as if it were local.

herein lies the context issue. if the call were functioning locally within the same process image, it would have the same env.

the rpc could be init'ed with context, but only global context. thread specific context (such as CWD) comes during runtime.

runtime context is transmitted with the rpc message.


- vm local funcs and executables

these are the module programmers product. the goal is to make module programming "language and host transparent."

the programmer designs a library func or executable which uses system services as usual.

another programmer wants to use the library, includes cosmos-hiena, adds a vm for the foreign/remote lib and uses cosmos_dlopen/sym to use the functions.



context and cosmos_dlopen() cosmos_dlsym()
---------------------------

cosmosdb context can be initialized into the dl pointer through cosmos_dlopen().  this context is propagated into the virtual function pointer through cosmos_dlsym().


using a func ptr
----------------

** this is superceded by transparent RPC via virtual functions. **

  val = dcel_val( dcel, &len );
  func_t_macro(val)(...);

or

  val = aframe_get_val( af, &len );
  func_t_macro(val)(...);

or
  aframe_exec(af, argc, argv);

or (cli)

  cosmos exec $fpath ...



bootstrapping core mods
-----------------------

create paths of access frames
to reference the module op structs.

  cosmos db
    aframe
      init
        file.ops
        cosm.ops
        lookup.ops


create paths of aframes to track open handles (in this case, from dlopen) so we can close the open handles later.

  cosmos db
    aframe
      open
        file.dlh
        cosm.dlh
        lookup.dlh


for each module, create a production instruction.

  prod instr
    fn_aframe: \0
    fn: dlsvc->open     // builtin
    context_aframe: \0
    argc: 1
    argv: { modpath }


run each prod instr to generate a dcel.  then, store dcel at aframe/open/<handle>.

for each, create prod instr

  prod instr
    fn_aframe: \0
    fn: dlsvc->dlsym     // builtin
    context_aframe: \0
    argc: 1
    argv: { "service_ops" }

run to create dcel and store at aframe/init/<module>






  



"/pathto"

  aframe
    dcel
      frag
        mfrag
          addr:"/pathto"
          svc:file
      dir
        dcel["mod.so"]
    branch
      aframe["mod.so"]

      
"/pathto/mod.so"

  aframe
    dcel
      prodi: source file $fpath
      frag
        mfrag
          addr:"/pathto/mod.so"
          svc:file
      dir
        dcel["func"]
    branch
      aframe["func"]

--derivative

  aframe
    dcel
      prodi: xform dlopen $dc1
      frag
        mfrag
          addr:"/pathto/mod.so"
          svc:dlopen
          buf:dlptr
          len:0
      dir
        dcel["func"]
    branch
      aframe["func"]

"/pathto/mod.so/func"

  aframe
    dcel
      prodi: lookup $dc2 $fnname
      frag
        mfrag
          addr:funcptr
          svc:ptr



