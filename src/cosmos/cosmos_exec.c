




        /* build result access name
           ex.
               "fnname-arg1-argN"
               "scale-5in-7in"
         */





struct access_frame *cosmos_exec_mapfn(
    struct cosmos *cm,
    struct access_frame *mapfn_af,
    struct access_frame *targ_af)
{
        struct access_frame *res;
        char *fnid;


        if(mapfn == NULL)
        {
                HIERR("cosmos_exec_mapfn: err: mapfn_af NULL");
                return NULL;
        }



        /* create result access frame */

        res = cosmos_mknod(cm, par, fnid, mode, 0);




        /* exec the func's dcel */


        dc = func->dcel;

        exfn = dc->exec_fn;

        res = exfn(cm, par, dc, argc, argv);

        resf->dcel = res;
        


        return resf;
}
