


test cosmos_exec
----------------


test_cosmos_exec:


    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int ac = 10;


    access_frame *af = aframe_new();


    dl = cosmos_dlopen( modpath );

    fn = cosmos_dlsym( dl, "arrinc(int, int *)" );

    fn(af, ac, a);

    cosmos_dlclose( dl );



