
accessframe
===========
aka( context_frame )

2019/02/25

the name may change back to context_frame.



context system
--------------

- data context
- access context


data context is the configuration of resources, related data and metadata that reside locally along-side and within data. htaccess files, libs and bin PATH are an example. they exist within the filespace of the data they affect.

access context is the configuration of resources which accompany a session, such as a shell login session or website visit. particularly the directory stack, shell env, browser config and visited-link history are notable.



context paths
-------------

context can be linked together to form trees and directed graphs.

a file system's directed graph of directories and links is an example of a data context graph.

a browser history is an example of an access context tree with a single axis, "back and forward".



context paths as file system
----------------------------

 lookup( ctx, str );

all ops are on ctx path nodes (context frames).

lookup is modular.



context frames and dcels
------------------------

a context frame encapsulates a dcel. a context frame is the product of a lookup. the dcel is the result of the lookup.

further lookups branch out from the context frame.




data context paths
------------------


there are two kinds of data context: data and meta.
 
data context represent the regular nodes of a file tree. 

meta context represent meta-directory branches in a file tree, in cosmos, the .cosm directory.

data path nodes are directed via 'par' and 'child' properties.



access context paths
--------------------

access path nodes store context for each level of a path lookup. examples of access path lookup can be name lookup or a query. 

what this design seeks to improve is the path'ing of iterative searches, file transformation and link traversal.

simply put, a file system can be represented by access paths, not data paths.




data vs meta aframes
--------------------

a lookup sequence will generate data aframes for each level of hierarchy scanned.

the metadir, .cosm, is a virtual directory present in all directories within the data tree.  it contains a version of the system root, which can be modified in cascades between data levels.

the .cosm system is available to the lookup function and influences lookup behavior by hierarchy level.

because it is a modifier of the access context, it is naturally a property of the aframe.

aframes are used within the .cosm directory branches, but if they contain .cosm directories, they will become infinitely recursive.

so the meta aframe behaves differently from the data aframe. 



meta directory cascading
------------------------

if the domain cell contains a mapping named identified as a metadir, the mapping shall be overlaid onto the metadir in the access frame.  this new overlay will be inherited by further access frames.

if the domain cell does not contain a mapping named after the metadir, the metadir will simply be inherited, verbatim, from the parent access frame.

if the metadir is written to at any level of the hierarchy, an attempt will be made to write into the dcel, thus "burning it in" into the domain. 


cascade behavior implementation
-------------------------------

cascade behavior is implemented at lookup time.  the data/meta aframe type is first determined and then journaled in the aframe.

if a metadir is requested and an aframe branch cache entry exists, the metadir lookup proceeds down the branch.

else the metadir is looked up on the branch axis with reverse traveling origin. (see cosmos_lookup.md)


metadir source binding
----------------------

a meta aframe is bound to an address like a data aframe.

meta aframes are flagged to differentiate them from data aframes.

meta aframes are overlayed via the dcel bind production.  the dcel contains the overlay stack, the aframe contains the dcel.

lookup within a bind-dcel proceeds first along a bind axis and then along a branch axis.  a branch axis lookup on a bind dcel must look in multiple bind sources and if multiple sources satisfy, will produce a branch access frame which also has a bind dcel.  like braiding  rope.  braided lookup.



access frame struct
-------------------

    dcel_t *dcel;
    dcel_t *env;
    flag_t is_meta;
    LOOKUPFN_T(*lookupfn);
    aframe_t *branch_cache;

the virtual metadir is a child in branch_cache.

the optional overlay metadir is sourced from the mappings within dcel.

the overlay is bound into the virtual metadir.

the branch cache of a data aframe has a default membership of one metadir.  the branch cache of a meta aframe is empty by default.





aframe paths
---------------------

  aframe_mkpath()
  aframe_mkflatpath()
  aframe_by_path_id()
  aframe_by_path()
  aframe_by_flatpath()


aframe is a product of lookup.  it can also be a product of a "virtual path" constructor which creates aframes that will satisfy lookups without any underlying dcels being mapped.

these are useful for generating paths at system init time, when no modules are available for mapping dcels.

aframe_mkflatvpath() constructs a path string and then uses the entire string to create a single flat entry in the branch cache.

in contrast, aframe_mkvpath() constructs/grows a chain of branches.

both constructors generate a target aframe which can be used to store an object in its dcel.

aframe_get_from_vpath_id() retrieves an aframe located at a single branch, is analogous to aframe_get_branch(), and if the id is generated by a flat path string, retrieves from a branch generated by aframe_mkflatvpath().

aframe_get_from_vpath() and aframe_get_from_flatvpath() both take string arguments.  the flatvpath variety treats it as a flat pathstring and does not parse the string.

a flat filesys can be implemented using aframe_mkflatvpath() and aframe_get_from_flatvpath().

however, creating a file system using only aframe vpaths misses the real purpose of using dcels, which is to provide flexible access into mixed data stores.  vpaths are meant to be used for access cache and bootstrapping dcel services.


access frame contructor functions
---------------------------------

  aframe_t *
  aframe_new( aframe_t *par, char *new_name );

if initialized with a par argument, the new aframe sets its own parent to par, inherits the parents meta flag, and if unset, inherits the metadir of par.

  new_aframe {
    branch_cache[".."] = par,
    is_meta = par->is_meta,
    if( !is_meta )
      branch_cache[metadirname] = par->branch_cache[metadirname],

  }

it adds itself to par->branch_cache[new_name].



mkdir's effect on access frames
-------------------------------

mkdir directly effects dcels.  it has no immediate affect on access frames.  access frames are a product of lookup.  they reflect the presence of directories within the dcel.

aframes without dcels can be used to construct virtual file trees.  these are essentially ephimeral as they have no data backing.  they can persist as long as the aframe tree is cached somewhere.

a cheap alternative to mkdir:

  aframe_mkvdir( par, childname )

this would be an alias of:

  aframe_new( par, newname )




prop: env
---------
dcel type with a buffer backing.

envars are accessed via these dcel functions:

  r = dcel_child( dcel, varname );
  val = dcel_read( r, &len );

a dcel convenience macro for above:

  val = dcel_child_val( dcel, varname, &len );


an access_frame method:

  val = aframe_envar( aframe, varname, &len );

above could be implemented thus:

  dcel = aframe_env( aframe );
  r = dcel_child( dcel, varname );
  val = dcel_read( r, &len );

