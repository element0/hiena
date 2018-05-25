


modules
-------

modules install under

    ~/.cosm/lib/cosmos/modules/



module cascading (via .cosm dirs)
----------------

as modules house multiple production functions (source, map, transform) they should cascade.


some modules do not need to cascade:

    lookup module
    source modules
    

some modules do need to cascade:

    mapper modules
    transformer modules



high-level interface
--------------------

modules follow the ASH paradigm.


a Address given to a Service function returns a Handle:

    struct cosmos_module *cosmos_open_module(struct cosmos *, cosmos_id_t, char *MODNAME);


use the module handle...

    modhdl->source();
    modhdl->map();
    modhdl->transform();


close the handle when finished

    cosmos_close_module(struct cosmos_module *);



low-level interface
-------------------

modules are accessed by cosmos path.

    mod = cosmos_lookup(cm, par, ".cosm/lib/cosmos/modules/MODNAME");


    hdl = cosmos_open(cm, hdl);


    cosmos_close(hdl);



implementation
--------------

using the cosmos-hiena framework itself, the following chain is used for module access:

    a = $module_pathname
    b = _omitted_

    c = dylib_mod->sourcefn(a)

    dylib_mod->mapfn(c)

    d = cosmos_find_child(c,b)
    e = cosmos_open(d);

    module_handle = e;



module pathname
---------------

a module pathname is built from the pathname of the .cosm dir plus module library path.  ie:

    $PWD + "/.cosm" + "/lib/cosmos/modules" + "/" + $modname + ".so"


using the PATH variable concept, multiple paths can be searched:

    ${PWD,HOME,INSTALL_ROOT} + "/.cosm" + "/lib/cosmos/modules" + "/" + $modname + ".so"

    


"mounting" parent sources
-------------------------

in order to use a module handle, its parent dylib must remain loaded.

the 'dylib_mod->mapfn' will use 'dylib_mod->svc' to open and close dylib during mapping.

we use 'cosmos_open' to cause its source root to either remain open or be buffered.



module 'open' cycling
---------------------

note:  two handle concepts: 1) module handle 2) product handle


a dcel's production instruction:

    FN_ID  MOD_ID  MOD_ARGS
    source file    ~/somedir/somefile.suffix

performing a file operation requires:

    open module handle
    run 'open' from module handle on args to make product handle
    run ops from module on product
    run 'close' from module on product

triggering a module's 'close' operation:

    opening a product handle increments the module's 'open' count
    closing a product handle triggers the module's 'close' operation








runtime loading (MOD: Modules On Demand)
---------------


bootstrapping:

essential modules are needed to access the modules.

    dylib_mod source module

these are loaded by cosmos init.



module initialization
---------------------

    cosmroot = sourcefn file ~

    lookupfn = lookup_mod->lookupfn

    lookupfn cosmroot ".cosm/lib/cosmos/modules/dylib.so.cosmos_module"
    
    ---

    targ = cosmroot
    
    map targ

    targ = find_child targ ".cosm"
    
    map targ

    targ = find_child targ "lib"

    map targ

    targ = find_child targ "cosmos"

    map targ

    targ = find_child targ "modules"

    map targ

    targ = find_child targ "dylib"

    targ = transform targ "so"

      /* if transform learns that
         targ is already its format,
         it passes targ through. */

    targ = transform targ "cosmos_module"

      /* cosmos_module sets a
         cosmos_module service on a
         dcel.  it has a compound 
         address of .so and symbol.
         
         use cosmos_open() to open
         a handle on module.  the 
         handle will contain the
         ops.
      */

    return targ

