








void *frag_mapsvc_open( void *fp, const char *mode )
{
        if( fp == NULL
         || mode == NULL )
                return NULL;

        struct hiena_frag *f;
        struct frag_fh *fh;
        struct frag_fh *fh1, *fh2;
        struct hiena_frag *f1, *f2;
        struct hiena_mfrag *mf;
        struct mfrag_fh *mfh;

        f1 =(struct hiena_frag *)fp;


        /* root fh outer refs self
         */
        fh = frag_fh_new();
        fh->frag = f1;
        fh->outer_fh = fh;
        fh->inner_fh = NULL;
        fh->mode = mode;

        fh1 = fh;

ffh_open_loop:

        if( frag_is_container( f1 ))
        {
                f2 = frag_get_first_content( f1 );
                if( f2 == NULL ) {
                        HIERR("frag_svc_open: f2 NULL");
                        return NULL;
                }
                fh2 = frag_fh_new();
                fh2->frag = f2;
                fh2->outer_fh = fh1;
                fh2->inner_fh = NULL;
                fh2->mode = mode;

                fh1->inner_fh = fh2;
                fh1 = fh2;
                f1 = f2;

                goto ffh_open_loop;
        }

        fh1->frag = f1;

        /* inner_fh can potentially
           ref self OK.
         */
        fh->inner_fh = fh1;

        return fh;
}

int frag_mapsvc_close( void *fhp )
{
        if( fhp == NULL )
                return 0;

        struct frag_fh *fh;
        struct frag_fh *ffh, *ffh0;

        fh = (struct frag_fh *)fhp;

        ffh  = fh->inner_fh;
        ffh0 = NULL;

        if( ffh != NULL )
        {
                

        while( ffh != fh )
        {
                ffh0 = ffh->outer_fh;
                frag_fh_cleanup( ffh );
                ffh = ffh0;
        }

        }
        frag_fh_cleanup( fh );

        return 0;
}


