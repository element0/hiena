
ARCHITECTURE
------------

platforms
---------
linux
windows
macos



products
--------
/usr/bin/snafufs
/usr/bin/cosmosd
/usr/lib/libcosmos.so
/usr/lib/cosmos.cosm/lookup/fudge.so
/usr/lib/cosmos.cosm/helper/grind.so
    /grind_int()
    ,grind_ext()
/usr/lib/cosmos.cosm/source/file.so
/usr/lib/cosmos.cosm/grinder/
/usr/lib/cosmos.cosm/types/ox.so
/usr/lib/cosmos.cosm/types/div.so
/usr/lib/cosmos.cosm/types/raymks.so
  <item templates>


$HOME/.cosm/lib/cosmos/modules/*.so


user generated products
-----------------------
scanners
xformrs
sourcerers
item templates
.cosm directories


description of api layers
-------------------------

`snafu_fs` uses `libcosmos` through the `cosmos.h` API.  It requests and operates on inos.  `cosmos.h` provides a set of file system operations compatible with the FUSE.

`libcosmos` spawns a `cosmosd` for each user as needed.  


`cosmosd` manages memory objects.  it uses `libcosmos` (`cosmos.h`).  it is completely transparent to the user.


`cosmos_lookup` performs a lookup by running a `lookup_module` from the `access_frame` of the lookup request.


a `lookup_module` uses `libcosmos` via a sub API: `lookup_svc.h`.


`lookup_svc` creates `production_instructions` and sends those to the `production_exec`.


the `production_exec` factors an instruction to other `production grid nodes`.  An un-factorable "prime" instruction is run.


the `production_exec` uses `scanner_modules`, `producer_modules` and `source_modules` from the `access_frame` of the lookup request.  the result is an `access_frame`.

the `access_frame` envelopes a `dcel`.

a factored instruction will result in multiple `access_frame` returns to the `production_exec`.  the `production_exec` merges these and returns a single `access_frame`.

production instructions can use modules from dcel's record.


api layers
----------

util, snafufs, scanners, xformrs, lookup

libcosmos

cosmosd

source_mods, access_frame, host_access_mod, dcel_production_mods

cosm, dcel, mapsvc, scanner_mods,
   grid

frag, mfrag, map_anchor

implementation primatives:
   btree, flat_array, hash_fn



object relationships
--------------------

  cosm-dcel 
  scan_def scan_prod scanner_mod


  cosm
  ----
  lookup_lib
  producer_lib
  scanner_lib
  service_lib


  lookup_mod
  ----------
  prod_instr  prod_fn_mod   dcel


  dcel    dcel_svc    dcel_fh
          dcel_mapsvc
  ----    --------    -------
  frag    frag_svc    frag_fh
                      frag_cursor
  ----    --------    -------
  mfrag   mfrag_svc   mfrag_fh
  ----    --------    -------
  file    file_svc    FILE


  btree
  ptr_list



psuedo-code (ox, fudge)
----------------

  

  snafufs( url.str )
    mountpoint = url.str
    fuseops = cosmos/fuseops
    root = cosmosd/init()
    fuseops/lookup(root,mountpoint)

  cosmos
    init
    fuseops
    get_access( ino )
    get_localhost_access()

  cosmos/init
    if no daemon, fork daemon

  cosmos/fuseops
    == cosmosd/fuseops

  cosmosd/fuseops
    lookup( ino, str )

  lookup( ino, str )
    access = axdb/get( ino )
    lookup_mod = access/cosm/lookup
    production_instruction =
      lookup_mod
      access
      1
      str
    return production_exec(
      production_instruction )

   

reference architectures
-----------------------

## REST ##

a domain is a sequence of media.

segments of media are "media fragments".

subsets of a domain, a set of media fragments, are represented by "domain cels".  may overlap.

media fragments are sequenced within a dcel via sequence fragments.  called "frags".

Frags are nesting.  Each domain cel has a root frag which will remain available for the life of the dcel.

Dcels are mapped via a nesting sequence of map cels.  These map to grammar rules as may be expressed by BNF.

Map cels are aligned on map anchors which attach to leaf level frags, (nearest the media fragments).

A dcel has a directory object which can bind its dirents to mapcels.


## ASH ##

In the implementation, sequenced objects are available for io via ASH achitecture:  address, service, handle.  Where service API closely mimics POSIX streams.

In example: the Address to a frag is given to a frag Service to open, resulting in a frag Handle which can be used with the service for io.

The dcel is available for mapping via a similar ASH where service is specialized API to adding, joining and navigating within the map cels.

A dcel's directory is available via ASH which follows the POSIX DIR api.


## SQL ##

The map cels within a dcel can be addressed by id and the content of an individual mapcel querried via a SQL-compatable internal API.


## Production Instructions ##

Each dcel is the product of a "production instruction".

Follows ASH:  A "prod instr" (address) is fed to a producer (service) which generates a dcel ( handle ).

## FUSE ##

FUSE file system creates a pipeline of production instructions for each file path lookup.


## Lookup Module ##

A modular interpreter for file path segments.  Used by FUSE fs to generate production instructions.


