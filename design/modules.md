


modules
-------

modules install under

    ~/.cosm/lib/cosmos/modules/



playground
----------

module functions are accessed by cosmos_lookup().

functions are executed by cosmos_exec().

modules are loaded as needed if the 
function is within a dylib.


procedure

- calculate module function path

- lookup module function frame

- execute module function frame




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

    struct module_handle *cosmos_open_module(struct cosmos *, cosmos_id_t, char *MODNAME);

    /* inputs are used to generate the address */


use the module handle...

    modhdl->source();
    modhdl->map();
    modhdl->transform();


close the handle when finished

    cosmos_close_module(struct module_handle *);






low-level interface
-------------------

modules are accessed by cosmos path.

    mod = cosmos_lookup(cm, par, ".cosm/lib/cosmos/modules/MODNAME");


    hdl = cosmos_open(cm, hdl);


    cosmos_close(hdl);




function access frame interface (alternate)
-------------------------------------------

    struct access_frame *cosmos_open_module_function(struct cosmos *, cosmos_id_t, char *MODNAME, char *FUNCNAME);

    struct access_frame *res = cosmos_exec(func_hdl, argc, argv, env);

    /* where env is a struct access_frame which includes ENV and sandboxed stdio */

    cosmos_close_module_function(struct access_frame *);


function access frame implementation
------------------------------------

lookup access path to function

    lookup ~/.cosm/lib/cosmos/modules/MODNAME.so.cosmos_module/transform
    -or-
    lookup ~/.cosm/lib/cosmos/modules/MODNAME.sh/transform


breakdown of productions (elids some access frames for sake of simplicity)

    par  = aframe:{ lookup_mod:fudge }
 
    home = aframe:{ 
        lookup_mod:fudge
        dcel:{ fnid:0, mod:file, argc:1, argv:{"~"} }
    }

    targ = lookup

    ...

    targ = source file "~"

    module_handle *mod
    mod->map = lookup "~/.cosm/lib/cosmos/modules/file.so/cosmos_map_fn"
    mod->svc = lookup "~/.cosm/lib/cosmos/modules/file.so/cosmos_service"

    /* we bootstrap the cache with the above paths already pointing to
       the following dcels */

        dcel:{ fnid:source, mod:module_function, argc:2, argv:{"~/.cosm/lib/cosmos/modules/file.so","cosmos_map_fn"}
               execfn:internal
             };
        dcel:{ fnid:source, mod:module_service, argc:2, argv:{"~/.cosm/lib/cosmos/modules/file.so","cosmos_service"}
               execfn:
             };

    /* the following modules are required */

        module:{ name:"module_function" service:{open,exec,close} };

                service:open = {
                                module_function_handle->internal_hdl = dlopen argv[1];
                                module_function_handle->function_ptr = dlsym argv[2];
                                return module_function_handle;
                        }
                service:exec = {
                                return module_function_handle->function_ptr(argc, argv, env_frame);
                        }
                service:close = {
                                dlclose module_function_handle->internal_hdl;
                                cleanup module_function_handle;
                        }

        module:{ name:"module_function" service:{open,close} };

                service:open = {
                                module_function_handle->internal_hdl = dlopen argv[1];
                                module_function_handle->function_ptr = dlsym argv[2];
                                return module_function_handle;
                        }
                service:exec = {
                                return module_function_handle->function_ptr(argc, argv, env_frame);
                        }
                service:close = {
                                dlclose module_function_handle->internal_hdl;
                                cleanup module_function_handle;
                        }

    
    



    cosmos_exectarg->module->map targ

    targ = lookup_child ".cosm"

    targ->module->map targ

    targ = lookup_child "lib"

    ...

    




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

    file_mod
    cosmos_module_mod

these are loaded by cosmos init.

the access path cache is primed with a path to the essential modules.





module access
-------------

    cosmroot = sourcefn file "~"

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

