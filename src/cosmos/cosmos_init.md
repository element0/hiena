

cosmos init
-----------

runs the daemon if not running.

daemon runs init procedure.

(there should only be one daemon per user per host - host/user/daemon)

init procedure creates cosmos db and loads essential modules:

  file sourcer
  lookup

now the daemon is able to take requests



run daemon
----------

check
  cosmosd run status
  cosmosd socket

fork daemon


create database
---------------

    cosmos db
        strings
        tree


about tree
----------

tree of access frames.

created by the lookup function, are paths of access frames which reach a dcel.

the access frame from which a request comes from may be matched by possible ACLs in the dcel.




load modules
------------


for each modpath
        load_mod


load_mod
        dlopen module path
        create aframe path
        stick dcel in aframe

  .c
        dl = dlopen( modpath );
        af = cosmos_mkpath(cm, apath_str);
        aframe_put_value(af, valtype, dl, len);



to get the module:

    af = cosmos_lookup(cm, apath_str);
    modptr = aframe_get_value( af );
    modops = modptr->ops;



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

  cosmos_mknod( aframe, prodinstr, ".cosm", mode, dev );


makes...

  cosmos_db
    tree
      .cosm







respond to lookup request
-------------------------

lookup requests can come from the file system user, or they can be internal, such as a reference within a prod instr.

access paths are created through the lookup process.


when snafufs runs lookup on example_mnt aframe

  lookup: example_mnt/.cosm/lookup

  lookup somename

---

lookup =
cosmos::get $aframe, ".cosm/lookup"

return =
lookup $aframe, $string

uses:
searches aframe.dcel.children
runs aframe.dcel.prodinstr
produces aframe.dcel.children




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

  
