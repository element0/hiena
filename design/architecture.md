
ARCHITECTURE
------------

This file describes
	1) the broad archetectural components of the system
	2) the API layers of the system
	3) synopsis of architectural paradigms, ie. REST, ASH


architectural components
------------------------

snafu fuse instance
	{*}-->{1} cosmos instance

cosmos instance
	--{ dcel db, axnode db, scanner db, string db }
	--> scanner modules
	--> lookup modules
	--> producer modules
	--> hiena library

hiena library

 

api layers
----------

util, fs_snafu, scanner_producer

lookup_fudge, exec_syssvc,
   access_paths

dcel_producer

cosmos_cosm, dcel, dcel_mapsvc,
   access_frame, scanner_lib,
   cosmos_grid

frag, mfrag, map_anchor

implementation primatives:
   btree, flat_array, hash_fn



description of architectures
----------------------------

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


