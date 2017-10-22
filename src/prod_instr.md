




production instruction implementation
======================

- rationale

- production functions and instructions

- production engine


rationale
---------

A production instruction's purpose is to rebuild a dcel when the underlying domain changes.

The production instruction has a pointer to a source dcel.  It belongs to a target dcel.  It produces a result dcel.

If the source is dirty, it must be synced and the production instruction re-run.  If the production fails, the target is invalidated.  If it succeeds, the result is compared to the target; merged if different, discarded if same.

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
