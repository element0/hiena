

cosmos init
-----------

runs the daemon if not running.

daemon runs init procedure.

there should only be one daemon per host


run daemon
----------

check
  cosmosd run status
  cosmosd socket


init procedure
--------------

uses libhiena/dcel

input gathered from host device
  cosmos.conf
    device user cosm root
    device user env root
    device user cosmos database
  device user


output
  cosmosd socket
  root access frame
  cosmos database


'device user cosm root' has
  lookup mod
  scanners
  source mods
  tools

  wizards
    sourcerer
    spellbinder
    summoner
    alchemist

  bin
  etc
    cosmos.conf
    hiena.conf
  lib
    scanners
      divine
      ox
    producers
    sourcers
      file
    tranformers
      to-divine
      to-html
  sbin
    lookup mod


input gathered from host device
-------------------------------

cosmos_init is platform specific code.


procedure w api dependencies
----------------------------

  file_sourcerer =
    load_mod( $file_mod_filepath )

  dcel_cosm_xformr =
    load_mod( $dcel_cosm_fpath )

  sourcelib.put( file_sourcerer )
  xformrlib.put( dcel_cosm_xformr )


  --- note
   source() uses sourcelib
   xformr() uses xformrlib
  ---



  root_cosm_dcel =
    source( $root_cosm_filepath )

  new root_access_frame = {
    cosm dcel = 
      xformr(root_cosm_dcel,cosm)

  cosm_from
    "scanners.slib" dcel =
      trans(src_dcel/scanners, slib)

  src_dcel/scanners.slib

  cosm/"lookup mod" =
    dcel dyload(conf/lookup_mod)

  cosm/"source mods" =
    dcel srclib_load(conf/source_mods)

  cosm/tools =
    dcel binlib_load(conf/tools)


now the root cosm is ready.

if we load another cosm

  src = dcel source($filepath)
  cosm = dcel cosm_from( src )

we can cascade cosm[1] onto cosm[0]

  cosm[2]
    = dcel cascade(cosm[0],cosm[1])


api required above
------------------

  dcel
      dcel cascade(dcel,dcel)

  productions
      dcel source(url)
      dcel srclib_load(dcel)
      dcel slib_load(dcel)
      dcel binlib_load(dcel)
      dcel dyload(dcel)

  cosmos
      dcel cosm_from(dcel)

  