cosmos cascade
--------------

the .cosm meta directory is available from every level of the hierarchy.

like .htaccess it is cascaded onto each preceding level's .cosm.



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



