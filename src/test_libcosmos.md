2018-09-04

test libcosmos


cosmos_init:

  new cosmosdb

  mknod cosmosdb/proto .cosm/vm/hostfn.vm

  init_svc cosmosdb

  init_lookupfn cosmosdb

  cosmosdb




test_libcosmos:

  cosmos_init > cosmosdb

  bind "file:///home/cosmos/" cosmosdb/tree

  cosmos_opendir(cosmosdb/tree)
  >
  dirh

  while cosmos_readdir(dirh)
  >
  dirent != NULL

    print dirent


  cosmos_closedir(dirh)

  cosmos_cleanup(cosmosdb)

  OK






init_svc:

  mknod cosmosdb/proto .cosm/lib/cosmos/svc/file.so


  dlopen .cosm/lib/cosmos/svc/file.so
  >
  cosmosdb/proto/filesvcmod.dlopen


  dlsym cosmosdb/proto/filesvcmod.dlopen "cosmos_opendir_fn"
  >
  .cosm/lib/cosmos/svc/file.so/opendir.fn


  echo "cosmos_hostfn"
  >
  .cosm/lib/cosmos/svc/file.so/opendir.fn@exectype




  dlsym cosmosdb/proto/filesvcmod.dlopen "cosmos_closedir_fn"
  >
  .cosm/lib/cosmos/svc/file.so/closedir.fn


  echo "cosmos_hostfn"
  >
  .cosm/lib/cosmos/svc/file.so/closedir.fn@exectype


  
  dlsym cosmosdb/proto/filesvcmod.dlopen "cosmos_readdir_fn"
  >
  .cosm/lib/cosmos/svc/file.so/readdir.fn


  echo "cosmos_hostfn"
  >
  .cosm/lib/cosmos/svc/file.so/readdir.fn@exectype

  


init_lookupfn:

  mknod .cosm/lib/cosmos/lookup/light.so/lookup.fn


  init_protomodule ".cosm/lib/cosmos/lookup/light.so" "lookupmod"


  init_protofn "lookupmod" "cosmos_lookup_fn"
  >
  .cosm/lib/cosmos/lookup/light.so/lookup.fn


  echo "cosmos_hostfn"
  >
  .cosm/lib/cosmos/lookup/light.so/lookup.fn@exectype



init_protomodule:
  > modfilepath, modname

  dlopen ${modfilepath}
  >
  cosmosdb/proto/${modname}.dlopen

  OK




init_protofn:
  > modname, fnname, modcosmpath

  dlsym cosmosdb/proto/${modname}.dlopen ${fnname}
  >
  ${modcosmpath}/${fnname}.fn


  echo "cosmos_hostfn"
  >
  ${modcosmpath}/${fnname}.fn@exectype

  OK

  
