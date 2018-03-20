

module system
-------------

a module's funcs are avail thru fudge.

  /pathto/mod.so/func

in fudge, the path can be resolved via a PATH resolution mechanism and via aliases.  In both, a shorthand func name expands to the full pathname.

and the full pathname resolves to an access frame pointer.


types of modules
----------------
modules must implement one or more of the following interfaces.

cosmos_lookup_fn()
cosmos_source_fn()
cosmos_bind_fn()
cosmos_grind_fn()



load_mod()
----------

load_mod() is used at cosmos init time to load modules and add their essential functions to the cosmos db.


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



using a func ptr
----------------

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



