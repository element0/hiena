








dcel_dirsvc
===========


contents
--------
- directories and dcels
- directories within map structure
- opendir algorithm
- readdir algorithm
- closedir algorithm
- d_name generating


directories and dcels
---------------------
a dcel has a top level mapcel.
if the top mapcel is a dir, the dcel is a dir.  opendir and readdir will access the directory of the top mapcell.



directories within map structure
--------------------------------
a mapcel hierarchy can represent a directory hierarchy

an example:

  larder:{ sour:{ grapes, apples }, sweet:{ potatoes, onions } }

  dir
  :=
  head body
       :=
       dirent fill dirent
        :=
  head body
       :=
       dirent fill dirent

  head := d_name 
  body := colon obrac ws? dirent ws? comma ws? dirent

access path:

  dir/dirent


directory object:

  mapcel->directory->mapcel(by_pos)


dirent properties:

  mapcel->children->mapcel(by_id)


opendir algorithm
-----------------
prepare directory handle for reading

inputs:
- dcel

outputs:
- directory handle {}
  - directory structure
  - directory position
  - directory cache structure
  - directory cache position

procedure:




readdir algorithm
-----------------
get one dirent at a time

inputs:
- dcel
- directory structure via opendir
- directory handle via opendir: {}
    - position
    - length remaining
    - current map anchor
- directory cache structure
    - location

outputs:
- dirent
- update directory handle's position
- update dcel's directory cache


procedure:

if dcel's dir cache is not stale
    - get dirent from cache loc
    - advance cache location
    - return dirent

-else-

get map anchor at dir handle's pos.
for each in anchor's child list where length is less than "length remaining plus one":
    - create dirent from child
    - add dirent to dcel's dir cache
    - return dirent

internal vars:
- child list cursor

for btree list




closedir algorithm
------------------
cleanup directory handle

inputs:
- directory handle

outputs:
- errno



d_name generating
-----------------

a scanner is in charge of naming it's dirent cels.

a scanner must add a "name" sub-cel to a directory mapcel.

    mapcel (dirent role)
        mapcel (d_name role)

if there is no "name" sub-cel present, we generate a unique name.


