@file prod_instr.md

production instruction design
=============================

the production instruction type, procedure and its use of modules through the cosmos file system and virtual functions.


overview
--------
A prod instr informs the master-vm about how to construct a piece of data. The result is recorded in a dcel.

A single instruction can be a function call or a statement of flow logic.

A prod instr object may be singular or compound, comprised of one or more instructions.




procedure
---------
To create a production instruction, use an initializer function:

    pi = pinstr_source_url( url );


The initializer parses the protocol name of the url into `module_id`, stores the remainder of the url as the `addr`. both are stored in the `prod_instr` object.
i

**the media fragments of the dcel's buffer reference the `prod_instr` as their source.**


The instruction is fed to the master_vm. the master creates a dcel with a link to the prod_instr.

  dc = mastervm_run_pinstr( pi );


the dcel is ready for action.









production instruction implementation
======================

- overview

- producer modules

- rationale

- production instructions and scanner mapping

- production functions and instructions

- production engine

- implementation




production instructions and dcels
---------------------------------

a dcel has a production instruction. a dcel is a product of a production instruction.

a prod instr has a service module and a vars datagram. it uses the vars datagram to store arguments and context.

the service module has stream functions and mapping functions that provide io for the dcel.  module functions use the datagram to access their arguments.



productions have functional categories:

  source
  map
  find
  bind
  grind


a 'source' production instruction initialized with a 'file:///filepath' argument will have a 'file' module and a 'filepath' arg. when the production is run, it will generate a blank dcel with a reference to the PI.

a 'map' PI with a dcel and a module as args, will use the the mapping function of the module on the dcel. the mapping function will modify the indices and property maps of the dcel.

a 'find' PI, 'find( dcel *par, str * )', returns a child dcel from the parent's map who's id matches the str. (the found dcel is not a product of find. it is a product of the mapper.)

a 'bind' PI takes one or more dcel args and stacks them in an overlay. a bind module is responsible for delivering io and directory listings in a coherent fashion, maintaining integrity of the component dcels.

run 'transform $module $target $args' to run the module on the target decel and generate a derivative cel.




examples:

    [1] = source "file" $dirpath
    [2] = map [1] "file"
    [3] = find [2] $subfile
    [4] = either_or [10] [11]
    [5] = either_or [12] [13]
    [6] = find [5] $subitem
    [7] = map [7] "divine"
    [8] = transform [8] "html"
    [9] = END

    [10] = map [3] "ox"
    [11] = transform [3] "ox"
    
    [12] = map [4] "dir"
    [13] = transform [4] "dir"

fudge expression of the above:

    file:///dirpath/subfile.ox.d/subitem.divine.html



bytecode array (`pilist_t`) of the above:

    8, 24*uintptr_t,
    PCMD_SRC, STR_PTR, STR_PTR
    PCMD_MAP, COSMOS_ID, STR_PTR
    pcmd_fnd, cosmos_id, str_ptr
    pcmd_map, cosmos_id, str_ptr
    pcmd_xfm, cosmos_id, str_ptr
    pcmd_fnd, cosmos_id, str_ptr
    pcmd_map, cosmos_id, str_ptr
    pcmd_xfm, cosmos_id, str_ptr


flow contol
    pcmd_if, pilist_ptr, pilist_ptr
    pcmd_ifn, pilist_ptr, pilist_ptr



find producers
--------------

(different find producers are possible.  a "find-multi" could merge multiple results into one container cel.  a "find-one-or-list" could return a single cel or a container cel if there are multiple matches.)


instruction processing
----------------------

evaluate the current instruction.
if it fails, return error.
if it is a special RETURN or END symbol, return value.

program stack tracks subroutines.



primative production function types
-----------------------------------

bind source,
bind overlay,
map,
find,
evaluate-transform



generative vs non-generative functions
--------------------------------------

true production functions:

'source', 'transform' and 'bind' create cels.



non-producing functions:

'map' and 'find' find cells.

(map creates multiple subcels at a time, but uses 'source' to generate them.)



    



production instruction language: objects
----------------------------------------

the language objects must be capable of processing by the grid computer.


    %type <uintptr_t> cmd arg

        instruction_list := COUNT LENGTH instr...

        instr := cmd arg arg
 

        cmd := PI_SRC
            |  PI_MAP
            |  PI_TRANS
            |  PI_FIND
            |  PI_BIND

        arg := 
            |  PI_PIPE_IN
            |  COSMOS_ID
            |  STR_ID
            |  DATA_PTR




production instruction core functions
-------------------------------------

command interpreter function:

        prod_exec(instruction_list)



production instruction language: commands
-----------------------------------------

        source
        select_children
        select_properties
        map
        bind_merge
        transform


        map parent_cosmos_id
        select_children parent_cosmos_id regex_str




command implementation
----------------------

commands are implemented within modules.  so the `file` module would have a `map` function which would map a directory to a child list and map file metadata to a properties list.



producer modules
----------------

a producer module has:

    - a production function
    - stream service functions
    - sync check functions

the service functions overload the standard dcel service functions.

ie.  bind-cascade module overloads dcel_write().  (bind-cascade creates a product of dcel 1 and 2, the result is dcel 3.  but writes must happen to dcel 2 or the cascade is not a cascade.)



rationale
---------

A production instruction's purpose is 
- generate dcel
- distributable processing
- rebuild cache
- data binding


The production instruction belongs to a target dcel.  It has a pointer to a source dcel.  It produces the target dcel.

A production instruction has sync check functions that can be called by cosmos.


If the source is dirty, it must be synced and the production instruction re-run.

The sync algo may alter the production instruction and or dcel.

If the production fails, the target is obsolete.  If it succeeds, the result is compared to the target; merged if different, discarded if same.

all productions must fit this model.



## example ##

a source dcel

   x{abcd}

a production instruction

   select * from "x" where "name" is "c";

a result

   c


a change in the frag map of the source

   x{acbd}

the target's production instruction

    select * from "x" where "name" is "c";

a result

    c

compare to target: the target has not changed, therefor the dcel memory object remains valid, as do it's references.  it should take the place of the "c" object in the updated source dcel's child list.



domain map validation
---------------------

if the parent dcel's checksum changes, the children may be invalid.

they are still valid if their checksum exists inside the map somewhere.

remember, the checksum may be more intelligent than a mathematical hash function.  it may 

scanner rule-path constraint:  allows a dcel to revalidate against an reconfigured mapcel hierarchy.


production instruction requirements for scanner mapping
---------------------------

to rebuild a map dcel from scratch we need

  - source dcel
  - scanner id
  - rule id
  - ordinal
  - rule id "path"
      (calc'd fr map)
  - rule id "path" constraint
      (set by scanner)



production instructions generated by a scanner mapping
---------------------------

The domain can change in two ways:  The order of its set; the content of its set.

In theory, if the order changes, a map cel can still be valid if it's checksum value is still valid.

(checksum may be complex, calculated from the dcel's canonicalized content map, not just its bytestream.)

the info that can rebuild a map dcel:
  
  fragment underlyer
  clipping "window" of frag
  checksum function for dcel
  checksum value
  parent map dcel
  source dcel for full map rebuild
  scanner and rule full map rebuild


## frag validation ##

To validate a mapping, the production instruction needs to reference the underlying fragment.  This can be done with a "window frag" - a map dcel's top fragment. If the fragment does not change, the dcel is valid.

## content validation ##

If the underlying fragment changes, it cannot be guaranteed that the map dcel will be valid.  The scanner will have to be re-run on the frag at the least, maybe the source dcel at the most.

Each map dcel's production instruction needs a checksum function (this can be a module or part of a module.)

If the map dcel's order within its parent map dcel changes, but the dcel's chcecksum is still present within the parent set, the dcel may be merged into the parent set.

## merging ##

merging is performed by keeping the original dcel object but swapping in the fragment info from the re-generated dcel.  also swap the dcel into the fragment's map anchor.




production functions and instructions
-----------------


a producer function:

        dcel *(*)(context_frame *, int argc, void **argv);


a production instruction:

    prod instr
        prod fn
        contx frame
        argc
        argv


ie.
   {dsource, myctx, 1, filepath}
   {dfind_sql, myctx, sqlc, sqlv}
   {dbind, myctx, dcelc, dcelv}
   {dgrind, myctx, argc, argv}
   


## production engine ##

the production instruction execution engine.

  dcel *prod_exec( prod_instr * );



## source function ##

the source function expects a url string.

        dsource( ... "file:///abc.txt" );



## bind function ##

the binder expects its argv to be dcels.  an array of dcels will suffice:

        dcel *dc[n];
        ...
        dc_new = dbind( dc );



## find function ##

a find function searches for and selects a map dcel from a source dcel.

the mapcel becomes the root mapcel of the result dcel.  result dcel's root fragment is a window of the (possibly larger) root fragment in the source dcel.  a window fragment has start and end boundaries which shall be respected during dcel service operations.


## grind function ##

the grinder casts its argv thus:

        argv[]={
            dcel *(*)(int, void **),
            void *,
            void *,
            ...
        };


the grind prod_fn expects a function pointer as its first argument.  the fnptr has a type of:

        dcel *(*)(int, void **);

the remainder args are passed to the function pointer.


## context frames ##

at its most robust, a context frame is an execution environment instance, which can be executed on any grid node and produce identical results.

at a bare minimum it is empty and ignored.

the environment



implementation
--------------


    prod instr
        aframe to prod fn
        fn ptr

