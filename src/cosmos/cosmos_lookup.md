

cosmos lookup
-------------

inputs:

cosmos database
access frame
path string


output:

access frame


procedure:

3 steps.

get parent access frame's lookup module.

use it to lookup current frame's internal lookup module from the .cosm branch.

use the internal lookup module to lookup path string.



detail:

lookfn = par->lookfn;

ilookfn = lookfn( cosmos database, access frame, internal lookfn path string );

ilookfn( cosmos database, access frame, path string );


example:

cosmos_lookup( db, mountpoint frame, relative path );



optomize
---------

             on every creation

aframe
   par
   lookupfn



vs

aframe
   par

vs

aframe
   branch
      "../.cosm/lookup.fn"


--

             on every lookup

aframe/lookup_mod()

vs

lookup_pathwalk( aframe/par, pathstr )

vs

lookup_branch( aframe, pathstr )



--
which happens more? aframe create or aframe lookup?

put the overhead on the least frequent operation.



access frames are created by the init procedure and by the lookup procedure.

