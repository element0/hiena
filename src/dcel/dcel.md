@file dcel.md


domain cell     {#dcel}
===========

[TOC]

- dcel model
- related architecture 
- dcel lifecycle

- interface architecture

- dcel structure
- database-analogy
- dcel-map
- dcel-mapcel hierarchy structure
- sql query strings for use in examples



dcel model
----------
2019-02-18 0610

    dcel
      production
      buffer
      fragmap
      map
      index

    production
      module
      prod type
      instructions
        (command,args)[]
      


dcel methods
------------
2019-03-17 2015

Service methods:

    stream io
    --
    open
    close
    getc
    read
    write

    rest
    --
    get
    put

    sql
    --
    select
    insert

    fs
    --
    touch
    mv
    rm
    cp



module methods
--------------
2019-03-18 0711

Modules may, at their discretion, overload dcel service methods.

Additionally, they may provide objects and commands which may be used in the `production instructions`.



related architecture  
-------------------- {#architecture}
2019-02-20


    master vm 
    production instructions (PI)
      master ops
      vm instructions
    master context    // see footnote*
    modules (mod)
      virtual functions (vfn)
      virtual machines (vm)
    domain cells (dcel)
      fragments (frag)
        media fragments (mfrag)


*master context - the os context from which the modules are drawn. in cosmos, this is the cascading os context.



media fragments
---------------

These are leaf nodes on the fragment tree. They refer back to a dcel and indicate boundaries within the dcel.

Media fragments do not need to refer back to the same cel as their container. They can reference other cells.



modules
-------

The module used to serve the dcel cannot come from within the dcel. It must be provided by an access context.

The access context is a path node and must have a lookup module to function. The lookup module looks at the path branches and then at the node's dcel if need be. If the dcel needs to be mapped, a map module must be run.

The lookup module looks in the path branches for a mapper, and then in the dcel, but this time if no mapper is found, lookup recurses backward into the context's parent.



contexts
--------
2019-03-19 0626


Domain Context surrounds and includes the domain (dcel).

Access Context surrounds the Domain Context and is present only during operations.

Domain Internal Context is the context within the dcel which surrounds the dcel's children and map fields.


lookup in context
-----------------
2019-03-19 1926

Access Context includes a lookup module and a file module by default.

Module functions run inside the contexts they are accessed in. The lookup module uses the Access Context as its resource.

After dcel creation, you can find the dcel's module in the Domain Context and run any of its functions, such as io or mapping.


Dcel data structures record module references within the `production` object. To recreate the dcel, pass the `production` object and Domain Context to the producer engine.

The modules are searched relative to the Domain Context based on MODPATH variable in the Domain Context's ENV.


index
-----
there are two indices: child and property.

the child index is where dirents are indexed by mapper modules.

the property index is where other significant values are indexed.

properties can be accessed by fudging the dcel from a directory to a property directory. the transformation generates a new dcel and maps the properties to the child index. (the transformer module will need to override the directory services so that new entries can be created and properly inserted into the original dcel.)




dcel lifecycle        {#lifecycle}
--------------
2019-02-20

Create production (PI), submit to master vm.

Master vm runs instruction, uses master context, vfn's and vm's to execute sub-instr's. Returns result in dcel.

Dcel is now a controller for the product domain via REST, stream io, directory, and SQL API's.

dcel can be mapped by the module indicated within the production instruction and run by the master vm, using additional production operations. The map is saved within the dcel.



example: production

   mastervm_source("ssh://host/file");

master runs local source operation, which sets source module "ssh" and address. no vfn's are run. returns dcel w service and addr inside `production`.

   --> myDcel.production.{svc,addr}


example: REST

   
   buf = dcel_get( myDcel, &len );

the dcel controller uses the REST interface of the PI svc module, returning an atomic result in `buf,len`.

   --> {buf,len}


example: mapping

   mastervm_map(myDcel,"ox");

the master vm runs local map operation which finds the mapping interface of module "ox", which in turn modifies dcel's map and index in place.

   --> myDcel.{map,index}  // modified


example: directory

   dirh   = dcel_opendir(myDcel);
   dirent = dcel_readdir(dirh);
   ...
   dcel_closedir(dirh);

the dcel controller reads a dirent from myDcel.index, or passes through to PI svc module if mod provides a directory interface. (passthrough avoids duplicating a directory in dcel if it already exists on another source.)




source code architecture
------------------------
2019-02-23

 dcel.c
    dcel control
 frag.c,mfrag.c
    buf ctrl
 mapcel.c
    map ctrl
 mastervm_ops.c
    source()
    map()
    find()
    bind()
    grind()
 vm_instr.c
    vm_instr ctrl
 mastervm.c
    uses mastervm_ops
    runs vm_instr's
    makes dcel's
    manages modules
    manages vm's
 module_interface.h
    mapper ops
    uses svc_interfaces
 svc_interfaces.h
    REST,stream,directory,SQL
   

 






dcel database analogy   {#database-analogy}
----------------------------------
2017-10-07 1745

a dcel directory is a table
a dcel is a single row in a table
ruleid's are column names



## domain cell map: complex table ##  {#dcel-map}

2017-10-08 0730

a domain cell can be visualized as a single row in a table.  the columns of the table are layered and nested to reflect the mappings.


dcel production and service module
----------------------------------
(see elsewhere Production Instruction)

a dcel has two "halves"

- producer state
- mapper state

producer state
- module name
- prodfn type
- cmd
- args
- producer private state


mapper state
- maps
- indices
- buffers
- open file states
- analyzer private state


producer and mapper functions exist within the module.

file stream operations are provided by the module.

when the mapper is run, the mapper reads and writes the mapper state and when needed, uses the file stream operations from the producer.





domain cell is the searchable unit
----------------------------------

2017-10-11 2046

mapcel is not searchable; is a leaf of info about length and ruleid.

the mapcel is useful in conjunction with the map anchor and the frag to create a searchable map.



indices
-------

2018-05-04 0718

`prop` index of map generated by hiena scanner.  a single key may index multiple mapcels.

          abstract values (not mapped to any stream) are also kept in this index.

          hiena abstract value:

          - scanner_id
          - rule_id


          snafuFS abstract value:

          - attr
          - xattr


          cosmos abstract values:

          - exec helper reference




accessor functions
------------------

2017-10-15 0600

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


dcel and stream io
------------------

  fh = dcelfh_open( dcel );

  numbytes = dcelfh_read( buf, len, fh );

  dcelfh_close( fh );


dcelfh_open() will use the fragment system to identify one or more source modules for its fragments, then will open a handle to a module...

the media handle open procedure will...

locate the 'module' in the cosmos file system:

  cosmos_lookup( cosmos, access_path, module_name );


next, open a module handle and populate the functions...

  mod_hdl = {
    .dl = cosmos_dlopen( module ),
    .open = cosmos_dlsym( dl, "void *open(char *addr)" )
  };


next, open a 'media_handle'...

  media_hdl.open( mfrag.addr );


store it within the dcel_fh file handle object.

  fh.media_hdl = media_hdl;



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

