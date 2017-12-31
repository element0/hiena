

cosmos init
-----------

runs the daemon if not running.

daemon runs init procedure.

(there should only be one daemon per user per host - host/user/daemon)

init procedure creates cosmos db and loads essential modules:

  file source
  lookup
  dcel-cosmos xformr

now the daemon is able to take requests


run daemon
----------

check
  cosmosd run status
  cosmosd socket

fork daemon


load modules
------------

for each path
        load_mod

load_mod
        dlopen path
        attach dl to dcel
        assign dl_service to dcel
        store dcel in cosmosdb
        attach dl to 

builtin
        dl_service



init host cosm
--------------



create volume dcel
------------------
(part of snafu but described here)

new dcel
    addr: $mountpoint
    svc:  file_module



respond to lookup request
-------------------------

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

  
