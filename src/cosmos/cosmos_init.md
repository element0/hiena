



cosmos simple syrup
-------------------

  new db
  new root aframe
  set root aframe parent to root
  create root service mappings with aframe paths
      lookup mod
      file mod
  bind root dcel to rooturl




lookup( root, somepathname ) will get lookup mod from root's parent.  (root's parent is root.)

  lookupmod = apath get object( root->par, lookupmod_relpath )


lookupmod will use dcel service interface.  dcel service interface looks up the service module of root's dcel.  this lookup requires the mod to be premapped to avoid feedback loop.





cosmos init
-----------

runs the daemon if not running.

daemon runs init procedure.

(there should only be one daemon per user per host - host/user/daemon)

init procedure creates cosmos db and loads essential modules:

  file sourcer
  lookup

it creates a host, runs host vm and cloud vm.

now the daemon is able to take requests.



run daemon
----------

check
  cosmosd run status
  cosmosd socket

fork daemon


create database
---------------

    cosmos db
        lookup dylib
        strings
        access tree



about access tree
-----------------

tree of access frames -- paths of access frames which reach a dcel.  analogous to file paths.

tree root created by init.  branches created by lookup function.

root is an access frame.

  cosmosdb
    tree    <-- root access frame



sidenote: access control.

the access frame from which a request comes from ("visitor context") may be matched by ACLs in the dcel.





configure
---------

use config.h to compile default values, override those if a config file is present:



config.h

  COSMOS_HOST_ROOT "/"

  COSMOS_CONFIG_PATH ".cosm/etc/cosmos:~/.cosm/etc/cosmos:" COSMOS_HOST_ROOT "/etc/cosmos"

  COSMOS_LIBPATH ".cosm/lib/cosmos:.cosm/lib/cosmos:"
COSMOS_HOST_ROOT "/lib/cosmos"

  COSMOS_VMPATH cosmos_path_search(COSMOS_LIBPATH,"vm");


  lookup_module "lookup/lookup.so"

  
load and spin-up vms
--------------------

(see "cosmos_exec.md")

vm's are lazy loaded from:

  COSMOS_VMPATH

localhost vm:

  COSMOS_VMPATH/$hostname




load and map builtins
---------------------

lookup module

  cosmosdb
    lookup_dl   // dlopen() to here

    tree
      lookupfn  <-- lookupfn aframe






map operating system into .cosm
-------------------------------


the cosmos db maps the existing file system starting with root.

  cosmosdb
    tree
      hostid   <- map root fs here



then maps the operating system into a proto directory:

  cosmosdb
    tree
      hostid
        .os    <- map os dirs here


using cosmos_bind(db, 




map root .cosm directory
------------------------

the root .cosm:

look for file://.cosm


  cosmosdb
    tree
      hostid
        .cosm    <- map cosm here



load modules
------------

  COSMOS_INIT_MODULES_PATH="/.cosm/lib/cosmos:/lib/cosmos:.cosm/lib/cosmos:~/.cosm/lib/cosmos:"


most modules are lazy-loaded -- triggered by cosmos_lookup.

some modules provide "built-ins" to cosmos.  though not technically built-in, they are loaded for the lifetime of the cosmos db.

these need to have access frames added into the access tree at init time.

    .cosm/lib/cosmos/modules/dylib
    .cosm/lib/cosmos/modules/dlsym
    .cosm/lib/cosmos/modules/lookup



each aframe has module functions in its branches:

    dylib/
        open
        close

    dlsym/
        open
        close


each branch has a dcel:

    (dcel):
        module_name: ""
        prodfn_type: "builtin"
        args: (fnptr)
        



the dylibs are loaded into:

    cm->openlibs


and the functions are assigned to the branches.


cosmos_config provides a list of initial "built-in" modules.

for each module the follow algo applied to load:



    for each
        load_mod


    load_mod
        dlopen module path
        create access frame
        create branches

    create branches
        for each op
            create access frame
            dlsym op
            assign to frame
            set exectype to builtin

    


init host cosm
--------------

the first time cosmos_init is called, create the host cosm:

  dlopen( filesvc );
  dlsym( filesvc_ops );

  prodinstr
    context_aframe: &(aframe)
    fn_aframe: \0
    fn: filesvc_ops->source
    argc: 1
    argv: { cosmfpath }

  cosmos_mknod( cosmosdb, tree, ".cosm", , mode, dev, prodinstr );


makes...

  cosmos_db
    tree
      ".cosm"



create a first access path
--------------------------

any

  cosmos_mknod( cosmosdb, tree, prodinstr, "", mode, dev );




respond to lookup request
-------------------------

lookup requests can come from the file system user, or they can be internal, such as a reference within a prod instr.

access paths are created through the lookup process (as well as explicit creation in the init procedure).



lookup state
------------

  cosmosdb,
  visitor aframe,
  target aframe,
  target dcel,
  inherited_lookup_fn_hdl,
  lookup_fn_hdl,
  result aframe



lookup procedure
----------------
(2018-08-12)

  lookup( cosmosdb, visitor context, domain context, lookup str );


domain context is an access frame id in the cosmos db -- this is the start of the lookup.


acquire lookup function.

grab inheritance lookup function from domain context frame's parent.

  inhlookup = domain context->par->lookupfn


use inheritance lookup to locate domain lookup fn.

  dlookup = lookupexec( inhlookup, cosmosdb, visitor context, domain context, lookupfn relative path )


use domain lookup fn to perform lookup.

  lookupexec( dlookup, cosmosdb, visitor context, domain context, lookup str );


requires:

  domain context aframe
    domain parent aframe
      lookupfn aframe

  lookup()
  lookupexec()
  aframe_exec()
  dcel_exec()
  dcel_exec_helper_internal()
  dcel_exec_helper_external()




init procedure
--------------

input gathered from host device

  host
  user
  cosmos.conf
    ROOT_COSM_PATH
    ROOT_ENV
    COSMOS_DB_FILE


output

  cosmosd socket
  root access frame
  cosmos database


ROOT_COSM has:

  bin
  etc
  lib
    scanners
      divine
      ox
      raymarks
      md
    services
      file
    tranformers
      to-divine
      to-html
      to-cosm
    lookup
      fudge


libcosmos key funcs
-------------------

  source()
  xformr()
  bind()
  cascade()
  exec()

  load_mod()


procedure w api dependencies
----------------------------

  file_svc_ino =
    load_mod( $file_svc_filepath )

  dcelcosm_xformr_ino =
    load_mod( $dcelcosm_fpath )

  lookup_mod_ino = 
    load_mod( $lookup_mod_fpath );

  root_cosm_ino =
    source( $root_cosm_fpath )

  /* source() looks in
    "/usr/lib/cosmos/svc/" 
    from the cosmosdb
    to find a service to match
    the filepath input.
    it produces an access frame
    as output and stores it in
    the cosmosdb at filepath key. */


  root_access_frame_ino = 
    xformr( root_cosm_ino, dcelcosm_xformr_ino )


now the root cosm is ready.

if we load another cosm

  src_ino = source( $filepath )

  cosm_ino = xformr( dcelcosm_xformr_ino, 1, src_ino)

we can cascade cosm[1] onto cosm[0]

  cosm_ino[2] =
    cascade(cosm_ino[0],cosm_ino[1])


we can lookup a path via:

  ino = lookup( ino_a, $filepath )


we can stat

  stbuf *stat( ino )


we can read

  fh *open( ino, mode )
  buf *read( ino, len_ask, &len_res)
  

we can list

  dir *opendir( ino )
  dirent *readdir( dir )


we can execute

  ino *exec( ino, argc, argv )

the execution results in an access frame which can be read and which can have multiple streams represented by file descriptors internal to the frame.



--------

  
