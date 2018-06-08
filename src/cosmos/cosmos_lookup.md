


location
--------
cosmos_fs.h/cosmos_lookup() 



lookup axis theory
------------------
(2018/06/08)

a lookup happens on an axis defined by a linkage of access frames.

- branch axis
- bind axis

the lookup has directionality along the axis.

- forward
- reverse

a lookup origin can be stationary or traveling (along an axis.)

- stationary
- traveling


the combinations we are interested in are:

- static-origin, forward-branch lookup (regular)
- reverse-branch traveling-origin, forward-branch lookup (cascade)
- forward-bind traveling-origin, forward-branch lookup (bind)


these methods implement the three kinds of lookup:

- regular
- cascade
- bind


binds vs. cascades
------------------

a cascade happens within a filetree from parent to child node.

a bind happens accross file trees between child nodes.

a bind can merge two nodes from different media together into the same semantic node.

a bind is complex where data must be merged: two nodes with the same address but differing content.  sync  algorithms must be used.

also, a mechanism for accessing one individual or another from the bind should be available.




cosmos lookup algorithm
-----------------------
(2018/06/08)


functions
- cosmos_lookup
- cosmos_lookup_cascade
- cosmos_lookup_bind
- lookup_cache
- lookup_map


cosmos_lookup( par, pathstr )
   for seg in pathstr
      if r=lookup_cache( par, seg ) 
      || r=lookup_map( par, seg )
         return r
      else
         return NULL
    

lookup_map( par, pathseg )
   if par.map OK
   && r=find child in par.map
      return r
   if mapfn = cosmos_lookup_cascade( par.par, pathtomapper )
   && mapfn( par )
   && r=find child in par.map
      return r
   else
      return NULL


cosmos_lookup_cascade( par, pathstr )
   while par OK
   && ! r=cosmos_lookup( par, pathstr )
      par = par.par
   return r || NULL




   
   






cascade lookup
--------------
cosmos_lookup() implements cascade behavior as described in cosmos_cascade.md


meta-dir recursion loop while looking for modules can be avoided by performing reverse tree lookup.






child list - map implementation
-------------------------------


dcel child list key

  uintptr_t, uintptr_t


first 8 bytes is hash of file basename wout suffix

second 8 is hash of suffix









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




module lookups
--------------


a bind product

  dcel:{ module_id: "file" }


a lookup

  .cosm/lib/cosmos/modules/file.so/cosmos_map_fn





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

