


cosmos_load_module
------------------

opens a code module and links it into the cosmos tree.

the module can be built-in, dynamically loaded or rpc.

we populate a struct of function pointers from the module:

  struct module_ops *ops;

a local module could provide a struct of function pointers but this won't work for rpc.

for rpc, we use cosmos_{dlopen,dlsym} which hides the rpc's behind function pointers. these pointers are generated by cosmos_dlsym at runtime.

there are different proceedures we can use:

  cosmos_load_module(modpath)
  {
  switch MODTYPE(modpath)
  case builtin:
    MODSYMBOL(modpath,ops)
    dlsym(NULL,modsymbol)
  case dylib:
    dlopen(modpath)
    dlsym(dl,ops)
  case rpc:
    cosmos_dlopen(cm, af, modpath, mode)
    for each in struct ops
     cosmos_dlsym(dl, RPCNAME(each))
  }


the other way

  case builtin:

    for each in struct ops
     cosmos_dlsym(dl, MODSYMBOL(modpath, each))
    
  case rpc:

    for each in struct ops
     cosmos_dlsym(dl, RPCNAME(each))

  case dylib:

    for each in struct ops
     dlsym(dl, RPCNAME(each))


The first seems more efficient because we don't have to calculate modsymbol for every function.



rpc and standardized module idl
-------------------------------

what language should we use?

this won't work if we are dlsym'ing out of the process itself as we need to identify a module namespace.

cosmos_dlopen() is our way to identify a namespace and to identify the idl.

because module loader code is centralized, all module vm's need to respond to a standard idl.