

cosmos lookup
-------------

inputs:

cosmos database
cosmos ino 
request string


output:

cosmos ino
modifies inode
modifies request cache
modifies dcel map



description:

cosmos_lookup takes a request string.  (a path string from snafu.)

cosmos_lookup checks the lookup cache in the inode.

cosmos_lookup deligates the request to the lookup function referenced in the inode.

the deligate function parses the string and returns an ino.





procedure:

1. look in the cache
2. run the lookup function


a)
get string id
get cache branch at string id
else (b)

b)
get parent access frame's (inode) lookup module.

use it to lookup current frame's (inode) internal lookup module from the cur frame's ".cosm" branch.

use the internal lookup module to lookup path string in cur frame.

put result in cache at string id



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

