

module system
-------------

a module's funcs are avail thru fudge.

  /pathto/mod.so/func

in fudge, the path can be resolved via a PATH resolution mechanism and via aliases.  In both, a shorthand func name expands to the full pathname.

and the full pathname resolves to a numerical id.


types of modules
----------------

mod_load() is used at cosmos init time to differentiate modules and add their essential functions to the access frames db.


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



bootstrapping core mods to paths
--------------------------------


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



