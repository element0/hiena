

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

  cosmosdb
    aframe
      .cosm
        dcel


create user-host-context root
-----------------------------

a context is a configuration that might impose different restrictions from another configuration, such as two different desktop environments running on the same host, under the same user.

a context access frame can share the same root dcel as another context, but the local .cosm will differ.

  cosmosdb
    aframe
      skinner@badfish
        context-demo
          "/"
            .cosm
              <demo config>
        context-fishbowl
          "/"
            .cosm
              <fishbowl config>

a generic default context exists

    cosmosdb
    aframe
      skinner@badfish
        "/"

each time cosmos_init is called, create a user-host-context aframe if needed.

  url: cosmos://user@host/context/

  cosmosdb
    aframe
      user@host
        context

using these calls:

  cosmos_mknod( aframe, null_prodinstr, userhost_str, mode, dev );

  cosmos_mknod( userhost_aframe, null_prodinstr, context_str, mode, dev );



create volume dcel
------------------
(part of snafu but described here)

each time snafufs is run, create a mountpoint aframe:

  url: cosmos://user@host/context/mountpoint
  url: cosmos://user@host/context/home/user/example_mnt

  cosmosdb
    aframe
      user@host
        context
          home
            user
              example_mnt


and create a prod instr.  fn_aframe is derived from context_aframe.

  prod instr
    context_aframe: &(aframe/user@host/context/home/user/)
    fn_aframe: &((context_aframe)/.cosm/svc/file/source)
    fn: &((fn_aframe)/dcel:value)
    argc: 1
    argv: { mountfpath }


run to create dcel and store dcel at example_mnt



respond to lookup request
-------------------------

lookup requests can come from the file system user, or they can be internal, such as a reference within a prod instr.

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

  
