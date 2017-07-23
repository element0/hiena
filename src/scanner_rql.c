
static Hpat *validate_rqfunc_args (Hsp *h, const char *s)
{
    if(h != NULL && s != NULL)
    {
	Hpat *pat = new_hpat_from_string(s);
	if(pat==NULL)
	{
	    HIERR("scanner_hdl:validate_rqfunc_args: hpat is NULL, abort routine.\n");
	    return NULL;
	}

	if(h->rq == NULL)
	{
	    h->rq = new_rq();
	    if(h->rq == NULL)
	    {
		HIERR("scanner_hdl:validate_rqfunc_args: can't create h->rq, abort routine.\n");

		hpat_cleanup(pat);

		return NULL;
	    }
	}

	return pat;

    }else{

	HIERR("scanner_hdl:validate_rqfunc_args: h or s are NULL, abort routine.\n");
        return NULL;
    }
}


void set_rqtarg (Hsp *h, const char *s)
{
    Hpat *pat = validate_rqfunc_args(h,s);

    if(pat==NULL)
    {
	fprintf(stderr, "sshsp:set_rqtarg: pat is NULL, abort routine.\n");
	return;
    }
    set_targ(h->rq, pat);

    return;
}


void set_rqdest (Hsp *h, const char *s)
{
    Hpat *pat = validate_rqfunc_args(h,s);

    if(pat==NULL)
    {
	fprintf(stderr, "sshsp:set_rqdest: pat is NULL, abort routine.\n");
	return;
    }

    set_dest(h->rq, pat);
    return;
}


void set_rqsrc (Hsp *h, Ppak *s)
{
    if(h == NULL || s == NULL)
    {
	fprintf(stderr, "sshsp:setrqsrc: h or s is NULL, abort routine.\n");
	return;
    }
    set_src(h->rq, s);
    return;
}


void set_rqmap (Hsp *h, int i)
{
    if(h == NULL)
    {
	fprintf(stderr, "sshsp:setrqmap: h is NULL, abort routine.\n");
	return;
    }
    if(h->rq == NULL)
    {
	h->rq = new_rq();
	if(h->rq == NULL)
	{
	    fprintf(stderr, "sshsp:setrqmap: can't init h->rq, abort routine.\n");
	    return;
	}
    }
    set_map(h->rq, i);
    return;
}


void set_rqop (Hsp *h, int i)
{
    if(h == NULL)
    {
	fprintf(stderr, "sshsp:set_rqop: h is NULL, abort routine.\n");
	return;
    }
    if(h->rq == NULL)
    {
	h->rq = new_rq();
	if(h->rq == NULL)
	{
	    fprintf(stderr, "sshsp:set_rqop: can't init h->rq, abort routine.\n");
	    return;
	}
    }
    set_op(h->rq, i);
    return;
}




void hsp_rq_init (Hsp *h, Ppak *p){
    if(h == NULL)
    {
	fprintf(stderr, "set_rqres: h is NULL, abort.\n");
	return;
    }
    if(h->rq == NULL)
    {
	h->rq = new_rq();
	if(h->rq == NULL)
	{
	    fprintf(stderr, "set_rqres: can't init h->rq, abort.\n");
	    return;
	}
    }
    set_res(h->rq, p);	
    rq_set_hsp(h->rq, h);
}



