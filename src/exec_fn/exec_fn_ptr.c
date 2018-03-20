



/**
 * @param cwf current working frame

 */



struct hiena_dcel *exec_fn_ptr(
    struct cosmos *cm;
    struct access_frame *cwf,
    struct hiena_dcel *fndc,
    int argc,
    void *argv )
{
        struct hiena_dcel *ret;
        struct hiena_dcel *(*fn)(struct cosmos *, struct access_frame *, int, void *);

        fn = dcel_get_value(fndc);

        ret = fn(cm, cwf, argc, argv);

        


}