

brainstorm:  mapping generates a production instruction for each dcel.  how simple can it be?
------------------------------

create a root dcel

  dcel = source $url

map the url

  dcel = scan $dcel


as the scanner matches rules it puts dcels onto a stack.  they are nested as the stack is reduced.

what is the instruction which produces a terminal map dcel?  it can only be tied to a byte position.  its producer does not yet know how it will be nested in the map.

simply, a production instruction for a terminal map dcel is a byte range over a media fragment.

a production instruction for a non-terminal mapcel is a byte range calculated from the reduced map dcels.


separation of production and sync
---------------------------------

once a domain has been mapped, the map must allow the domain to change without requiring a complete remap. the scale of an unlimited virtual file system makes complete remaps impractical.

a sync algo should be allowed to change a dcel's prod instruction w out changing the dcel's identity.


life cycle of a dcel (relevant to production instructions)
----------------------------------------------------------

a prod instr is submitted to N compute nodes (the "grid").

  source $url

the grid runs the instruction.  outputs a dcel to the db and returns a dcel id.

  scan $dcelid

grid runs it.

the mapper creates map dcels

  map $dcelid $start $end $scannerid $ruleid

outputs a mapped dcel to the db and

  bind $dcelid $map-dcelid

merges into the dcel into $dcelid.

  find $dcelid '* from "child" where "name" is $findme'

grid runs. outputs dcel. 
ret dcelid.



  

