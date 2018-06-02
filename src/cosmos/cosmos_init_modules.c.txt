/* maybe not... */


int cosmos_init_modules(struct cosmos *cm, int modc, char *mod_path[]) {

        /* call from cosmos_init.
           cosmos_init has checked
           the args */

        struct access_frame *af;
        void *lookmod;

        char buf[PATH_MAX];
        char *bufptr = &buf;
        char *dsav;


        dsav = getcwd(bufptr, PATH_MAX);

        if( dsav == NULL )
        {
                if( errno == ERANGE )
                        HIERR("cosmos_init_modules: err: getcwd ERANGE");
                else
                        HIERR("cosmos_init_modules: err: getcwd NULL");
                
                return -1;
        }


        chdir(mod_path[0]);


        af = cm->aframe;


        cosmos_ll_mknod_path(cm, af, "init/lookup");



        if(( lookmod = cosmos_loadmod(cm, "init/lookup", mod_path[2])) == -1)
        {
                HIERR("cosmos_init_modules: err: lookup not loaded");

                return -1;
        }

        
        af = cm->proto;
        if(af == NULL)
        {
                HIERR("cosmos_init_modules: err: cm->proto NULL");

                return -1;
        }


        if((af->lookfn = dlsym((void *)aframe_val_ptr(lookmod), "cosmos_lookup_fn")) == NULL )
        {
                HIERR("cosmos_init_modules: err: proto->lookfn NULL");

                return -1;
        }



        af = cm->aframe;

        cosmos_ll_mknod_path(cm, af, "init/filesvc");


        if( cosmos_loadmod(cm, "init/filesvc", mod_path[1]) == -1)
        {
                HIERR("cosmos_init_modules: err: filesvc not loaded");

                return -1;
        }


        chdir( dsav );

        return 0;
}
