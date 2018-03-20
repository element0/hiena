









struct access_frame *cosmos_exec(
    struct cosmos *cm,
    struct access_frame *af,
    struct access_frame *func,
    int argc,
    void *argv )
{
        struct access_frame *res;
        char *fnid;


        /* build result access name
           ex.
               "fnname-arg1-argN"
               "scale-5in-7in"
         */
        



        /* create result access frame */

        resf = cosmos_mknod(cm, par, fnid, mode, 0);




        /* exec the func's dcel */


        dc = func->dcel;

        exfn = dc->exec_fn;

        res = exfn(cm, par, dc, argc, argv);

        resf->dcel = res;
        


        return resf;
}