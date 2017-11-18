

sync
----

big topic.  little word.



when the underlyer for a domain cel changes, we must find out whether the cel is still valid, can it be conformed or is it history?


dcel_sync_mod could be a module which analyzes and conforms old dcels to new dcels.  


examples of sync situations
---------------------------

a dcel is created

  source $url

then the bytestream at the url changes.

is the dcel valid?  yes.  it is valid because it is a product of the url.

however it should throw a sync flag so its dependencies know what to do next.

a dependency could be

  scan $dcelid

this would produce one or more map area dcels via

  map $dcelid $start $end $scannerid $ruleid

the map dcel would be relative to a portion of the bytestream.  if the stream changes, is the map dcel valid?  maybe.

it might be valid bc the underlier has not changed locally enough to invalidate the mapping.  it might be valid because the underlier rearranged the map without breaking the scanner rules.  it might be valid bc the underlier rearranged the map and changed the sequence but shifted the byte content to a different offset.

it might be invalid bc the underlier changed and broke the scanner rules.

it might be invalid because the pattern was removed.

it might be false-valid because the map changed but the scanner is to coarse to detect it. 

for this, we need a sync algo.  and we want to modularize it because it will probably need to be improved.


causes of change
----------------

- a value was replaced
- a set was reordered
- a member was moved from one set to another
- a member was deleted
- a member was duplicated
- cats and babies (external interference)
    - edit began but discontinued because author had to switch trains
    - cat or baby jumped on keybd
    - toaster caught fire


possible sync algo
------------------

sync should be maintained at the file fragment level and at the dcel level.

- find out which fragments have changed
- remap fragments
- conform old map to new



source bytestreams may be remotely hosted and unable to provide checksums.



 with a checksum.

if the fragment changes the file is marked as modified - but the surrounding frags are not.

each frag is achored to a tree of mapcels.  if the frag is unchanged, the topmost cels are added to the parser stack and scanning shall restart after them.

the new map is matched