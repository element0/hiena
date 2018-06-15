


struct access_frame *cosmos_exec( struct cosmos *cm, struct access_frame *mapfn_af, struct access_frame *targ)
{

        struct access_frame *res;
        char *fnid;

        /* build result access name
           ex.
               "fnname-arg1-argN"
               "scale-5in-7in"
         */

        /*
        res = cosmos_mknod(cm, targ, fnid, mode, 0);

        dc = func->dcel;

        exfn = dc->exec_fn;

        res = exfn(cm, par, dc, argc, argv);

        resf->dcel = res;
        */


        return res;
}





struct access_frame *cosmos_exec_mapfn( struct cosmos *cm, struct access_frame *mapfn_af, struct access_frame *targ)
{
        
        if(mapfn_af == NULL)
        {
                HIERR("cosmos_exec_mapfn: err: mapfn_af NULL");
                return NULL;
        }



        mapfn = aframe_value(cm, mapfn_af);



        mapfn(cm, targ, env_af);


        return targ;
}
