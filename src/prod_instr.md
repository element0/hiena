




production instruction implementation
======================


a producer function:

        dcel *(*)(context_frame *, int argc, void **argv);



## source function ##

the source function expects a url string.

        dsource( ... "file:///abc.txt" );


## bind function ##

the binder expects its argv to be dcels.  an array of dcels will suffice:

        dcel *dc[n];
        ...
        dc_new = dbind( dc );

## find function ##

a find function searches for and selects a mapcel from a source dcel.

the mapcel becomes the root mapcel of the result dcel.  the dcel's root fragment is a window of the (possibly larger) root fragment in the source dcel.  a window fragment has start and end boundaries which shall be respected during dcel service operations.


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