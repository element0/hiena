cosmos cascade
--------------

the .cosm meta directory is available from every level of the hierarchy.

like .htaccess it is cascaded onto each preceding level's .cosm.



systemwide behavior of a cascade
--------------------------------

on a posix file system, the root has mountpoints for other file systems.

    /
        media
            mountpt

the root also has directories for the operating system of the host:

    /
        bin
        dev
        etc
        lib
        sbin

in the case of cosmos we can put those directories into a "cosm" directory:

    /.cosm
        bin
        dev
        etc
        lib
        sbin


through cosmos, every subdirectory will have access to a local clone of its parent's ".cosm" directory.

    /
        .cosm
        home
            .cosm
            tom
                .cosm
        media
            .cosm
            tomthumb
                .cosm


casacade inheritance, softlinks and network-shared directories
----------------------------------

any given subdirectory inherits the cosm from its parent.

should a softlink inherit from multiple parents?

a given subdirectory can be shared among devices -- grafted into their file trees at arbitrary locations.  this is like soft-linking accross file system boundaries.

does the subdirectory inherit from multiple devices?

the fudging of a url such that the transformations rely on a specific .cosm.  the .cosm must be inherited by the shared folder in order to share a relative fudge url -- even if the .cosm comes from another device.


implied inheritance:

the act of a user sharing a directory between devices implies permission to inherit from the original device.  if a share-holder wants to use its local assets in a fudge, it seems we should provide a way to *add* additional inheritance:

an "inherit-local-cosm" operation which binds the local over the remote (and writes the product into the shared filespace.)  or, an implicit "lazy-auto-inherit" behavior of the system, which inherits from each device as fudges are generated.

what about a subdirectory of a shared directory?

   local
      share
         sub


the shared directory may have the following sources:

    deviceA://home/bob/share
    deviceB://home/dan/cur/proj/share
    deviceC://home/ned/proj/share

the shared directory is assumed to be equivalent among devices.  however, the cascading os from each system can only be available as far as permissions extend to each user.


the sub directory could be a simple directory, but is possibly a fudged map or transform product.

    deviceA://home/bob/share/sub.xform.map/

in which case, the transformer and mapper are implicitly available to all three devices and users.

even if the cosms are not shared explicitly, a fudge lookup may succeed on one of the devices and thereby provide access to the functionality - even if the code object is not accessible.

so why not make it accessible?  because sharing would imply receiving.  if bob added ned to the sources, ned's system would be exposed - not the threat of altering his system, but the threat of taking whatever code objects were there.

(on a side note, what if those code objects were architecture specific? they would only run on one of the devices or another.)


dark matter.  (negative)

let a fudge succeed mysteriously in the shared space if it fails in the local space.  only explicitly shared .cosm material will be available.


cross pollenation.  (fave)

each source also exposes its .cosm resources but may reside remotely.  each resource within a .cosm must have a dominant version.  the dominant version will run -- possibly on a remote machine.


arsenal computing.  (fave)

each device in the cosm is available as a virtual host.  a fudge operation may use any of the hosts capabilities which run either locally virtualized, or remotely on the real device.

each executible asset within a given .cosm has a membership in one or more virtual hosts.

    executible  vers   hostA   hostB
    ----------  ----   -----   -----
    crop        2.0    yes     yes
    warp        1.5    no      yes


union virtual host.  (goal)

the point of the .cosm is to provide a unified virtual host for fudges run on any device.  therefor, it should be available in uni-form to all devices.




platform independent union os through platform inter-dependence and rich aggregation
------------------------------------

we will now try to design a single file system expressing a union of a number of heterogenous platform devices:


  .cosm
    bin
      prog      <- link to choice
    devices
      a
        .cosm
          bin
            prog   <- choice
          kernel.vm
          src
            prog
              install
      b
        .cosm
          bin
            prog
          kernel.vm
          src
            prog
              install
    kernel.vm  <- def virt machine


if the prog would run on the localhost's kernel based on it's devices kernel, we can use a sandbox like 'lxc'.

otherwise, we have to use a vm with a different kernel or an emulator.

or we have to compile from source.

last case, we execute remotely on the original device.




use case: device clones
-----------------------

a subdirectory from a master system can be used as a netboot root for a number of devices.

the .cosm of the master subdirectory inherits the subdirectory's parent's .cosm -- including whiteouts.

thus a change to the master's root .cosm propogates to each subdirectory and subsequent devices which netboot from a subdirectory.



when the cascade occures:
-------------------------

our options for hooks are
- mkdir
- opendir
- readdir
- lookup
   - of ".cosm"


cascade algo
------------

the access_frame object can be chained in a cascade-chain.

if a lookup fails in one frame, lookup in the next in the chain.

cosmos lookup should keep a stack of cascade bind-points which are traversed.  if the lookup fails at any path segment, revert lookup state to the last cascade bind-point, switch to the next chain element, and redo the lookup from there.




--?old

use dcel bind producer, bind-cascade, in series to create a series of binds

the bind-cascade producer takes two dcels and outputs a third



sync
----

when an aframe changes, its dcel is subject to change.

when a dcel changes, its derivatives are subject to change.

a dcel has a generation number and a generation number of its parent _fragment_.

when the parent-generation number becomes out of sync with the number in the actual parent the dcel's production must be re-run.



