


domain cell
===========

- dcel database analogy
- domain cell map: a complex table
- dcel-mapcel hierarchy structure
- sql query strings for use in examples


2017-10-07 1745

dcel database analogy
---------------------

a dcel directory is a table
a dcel is a single row in a table
ruleid's are column names


2017-10-08 0730

domain cell map: complex table
------------------------------

a domain cell can be visualized as a single row in a table.  the columns of the table are layered and nested and reflect the mappings.


2017-10-11 2046

domain cell is the searchable unit
----------------------------------

mapcel is not searchable; is a leaf of info about length and ruleid.

the mapcel is useful in conjunction with the map anchor and the frag to create a searchable map.


2017-10-15 0600

accessor functions
------------------

  child_list_add( dcel, dcel_ptr );

  child_index_add( dcel, ruleid, value, dcel );

  dcel *child_index_get( dcel, ruleid, value );

  prop_index_add( dcel, ruleid, dcel );

  dcel *prop_index_get( dcel, ruleid );

  find_state *find_mapcels( dcel, ruleid );

  index_state *index_mapcels( dcel );



dcel-mapcel hierarchy structure
-------------------------------

2017-10-06 2300

  dcel
    prod instr
    frag ptr          // frag map
    scanner id        // mapcel area
    rule id
    len
    map list[#]       // prop tab
        dcel ptr
    map index[$ruleid]
        dcel ptr
    map index build state
    dir list[#]       // child tab
        dcel ptr
    dir index[$ruleid]
        index[$value]
            dcel ptr list[#]
                dcel ptr
    dir index build state

  anchor
    mapcel index[$len]
      mapcel ptr

  frag
    anchor index[$off]
      anchor ptr
    child frag index[$off]
      frag ptr
    mfrag ptr
    start offset
    end offset

  /* 2017-10-16 eliminate mapcel */

  mapcel
    head anchor // move to frag
    tail anchor // move to frag
    scanner id  // move to 
    rule id
    len
    child list[#]
        mapcel ptr


sql query strings for use in examples
-----------------

2017-10-09 0615

  select "name" from "child";

  select "name" from "child" where "type" is like "synopsis";

  select "name" from "prop"




dcel and map scanners
---------------------

2017-10-12 1513

a dcel is a product of a production instruction.

when a map scanner generates a dcel within a map, it must create a production instruction.

ie:
the root dcel will be generated with a "source" production.

the mapper identifies a subcel, and generates a "select" production:

  select $src_dcel $scanner $ruleid $start_off $end_off

if the src_dcel is altered, the select production can be verified against a new map of the src_dcel.  if nothing changes within the map dcel, the dcel remains valid.


dcel validity: map and frag
-----------------------

validity is a balance between map and frag.  a dcel 





dcel and sql
------------

  select * from "child";
  select * from "prop";

an sql runs as a production instruction and returns a dcel as its output.

the output could be a new stream -- or rather appear as one by a sequence of frags.



dcel and readdir()
------------------

opendir() would produce an iterator to the dcel's raw child list.

  for each
  {
      d_ino  = each->mapcel;
      d_name = select("name", each->prop);
  }

d_name is a dcel.  you can get its value by using dcel_svc_read() or dcel_svc_getchar().


concatenating dcel content
--------------------------

2017-10-12 1550

you can concatenate dcels in sequence by using a production instruction:

  select $dcel_1 $dcel_2 [...]



searching a dcel child list
---------------------------

2017-10-12

a dcel keeps a directory of dcels which represent children.

children can be selected by ptr or iterator.

  get(dcel,childptr);
  
  for each in dcel->child { ... };

getting a child by ptr returns an iterator which can be used to step forward or backward in the child list.


searching a dcel by child index
-------------------------------

2017-10-11 1558

dcels contain 0 or more child indexes.  these indexes correspond to members of the prop index of each child.  in other words, columns in the child table.

if the index does not exist it is create when queried.



searching a dcel for a property
-------------------------------

satisfies:
  select $prop_expr from "prop"


prop_expression:
   - a list of property ids
   - a single property id
   - a hierarchical property id
   - an ordinal property id

eg
  select "name" from "prop"
  select "name, size" from "prop"
  select "stat/atime" from "prop"
  select first "alias" from "prop"

the property id is expected to be a rule_id from one or more of the scanners which have been used to map the dcel.

a scanner can be explicitly requested:

  select "divine::name" from "prop"

if a property id does not match an existing property, it triggers a scan or an evaluation.

an evaluation:

a property id may match a scanner rule id or a scanner provided evaluation function.  The output of the function is the value of the property.  in this case the value might not be recorded explicitly in the source stream and is cached in the property index and removed if the dcel changes.



FUNCTION: dcel_find_mapcels()
-----------------------------

Returns a list of ptrs to dcels.

The dcels function as atomic units which encapsulate a mapcel and a fragment.

The production instruction which produces each dcel is iterative.

ProdInstr: find all matches to rule id within map of target dcel.

eg.

  find * from "prop" where $ruleid like $value

  might produce:

    dcel[0]
    dcel[1]
    dcel[2]

dcel[1]'s prod instr cannot be:

  find 2nd from "prop" where $ruleid like $value

because if the frag map got rearranged, the ordinal would change.

dcel[1]'s production instr could be:

  grind make_mapcel_dcel $mapcel $frag

if inputs $mapcel or $frag become invalid the production becomes invalid.



FUNCTION: index_mapcels()
-------------------------

inputs: dcel{ mapcel, frag }
outputs: index

  index
    reentrant state
    btree


ALGORITHM: 

for mapcel, read each mapcel in children list; produce dcel of each value and add to index at key: each->ruleid

each->value can be described by a dcel of {mapcel, new frag}

(each->value is generated rather than structured

where new frag is window frag on the fragment within the input dcel.

