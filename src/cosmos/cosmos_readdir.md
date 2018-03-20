



cosmos_readdir
--------------


inputs:

aframe remappings
dcel dname index
cosmos string db


outputs:

directory list



procedure
---------

for each in dname index
  apply aframe remappings
  expand string
  add to directory list




aframe remapping
----------------

aframe remap is three columns:

   dname, display name, lookup str


all three are hash ids of strings in the strings db.


on readdir, if the dname from the dcel's dname index matches col 1, the value is replaced by col 2.

on lookup, if the lookup str matches col 2, the lookup str is replaced by col 3.



example
-------


aframe dirmap
    some.ox, some.d, some.ox.d
    a.png, a.jpg, a.png.jpg


    aframe dirmap maps the dcel dirent to a new display name in the aframe and maps that to a lookup string.  the lookup string can be used to perform a lookup which will result in a new aframe on lookup.


dcel dir index by name
    some.ox : dc001
    a.png : dc002
