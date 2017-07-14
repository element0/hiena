




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