#include <string.h>
#include <errno.h>
#include <stdlib.h>



#include "dcel.h"
#include "dcel_mapsvc.h"
#include "dcel_svc.h"
#include "hpat.h"
#include "hierr.h"
#include "rql.h"
#include "scanner_hdl.h"


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


char *hsp_getenv(const char *envarname)
{
    return getenv(envarname);
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





Hspops *hsp_ops_create() {
    Hspops *ops = malloc(sizeof(Hspops));
    memset(ops,0,sizeof(Hspops));

    return ops;
}

Hspops *hsp_ops_init() {
    Hspops *ops = hsp_ops_create();

/*
    ops->make_ob    = ppak_make_ob;
    ops->set_bounds = ppak_set_bounds;
    ops->set_buf    = ppak_set_map_buf;

    ops->add_prop   = ppak_add_prop_hsp;
    ops->add_child  = ppak_add_child_hsp;
*/


    /* RETIRING... */
/*
    ops->putob  = hiena_map_putob;
    ops->gettok = NULL;
    ops->fopen  = dcel_svc->open;
*/
    /* ...RETIRING */

    /* CONTEXT FUNCTIONS */
    ops->getenv = hsp_getenv;


    /* REQUEST BUILDER FUNCTIONS */
    ops->set_rqtarg = set_rqtarg;
    ops->set_rqdest = set_rqdest;
    ops->set_rqsrc  = set_rqsrc;
    ops->set_rqmap  = set_rqmap;
    ops->set_rqop   = set_rqop;

    return ops;
}

int hsp_ops_cleanup(Hspops *ho)
{
    free(ho);
    return 0;
}


/*== OBJECT IMPLEMENTATION: hiena scanner payload == */

Hsp *
hiena_scanner_payload_create() {
    Hsp *hsp = malloc(sizeof(*hsp));
    memset(hsp,0,sizeof(*hsp));

    return hsp;
}

void
hsp_cleanup(Hsp *hsp)
{
    if(hsp == NULL)
    {
        return;
    }

    /* garbage collector */
    /*
hiena_parse_packet_take_out_the_garbage(hsp->parseroot);
    */

    /* RQL lookup workspace */
    if(hsp->rq != NULL)
    {
        rq_cleanup(hsp->rq);
    }

    if(hsp->lexer != NULL)
    {
	hsp->scanner_ref->op->yylex_destroy(hsp->lexer);
    }
    
    if(hsp->dfh != NULL)
    {
	dcel_svc->close(hsp->dfh);
	hsp->dfh = NULL;
    }

    /*
    hsp->src_ref
        -- reference pointer,
           do not cleanup.
    */

    free(hsp);
}




static Hsp *verify_hsp(Hsp *h)
{
    /* make sure hsp values follow proper constraints 
       as notated in the comments of "hsp.h"
       IF NOT cleanup 'h' and return NULL.
     */
    if(
	    h->dfh	   == NULL ||
	    h->op          == NULL ||
	    h->rq          == NULL ||
	    h->src_ref     == NULL ||
	    h->scanner_ref == NULL ||
	    h->slib_ref    == NULL  )
    {
	fprintf(stderr,"verify_hsp: hsp fails constraint check, abort\n");
	hsp_cleanup(h);
	return NULL;
    }
    return h;
}

Hsp *hsp_init(Ppak *data)
{

    Hsp *hsp = hiena_scanner_payload_create();

    if(hsp == NULL)
    {
        HIERR("hsp_init: can't create hsp, abort routine.\n");
        return NULL;
    }

    /* garbage collector */
    hsp->parseroot = dcel_new(NULL);

    hsp->src_ref = data;

    /*OPEN FILE STREAM*/

    if(data != NULL)
    {
        hsp->dfh = (struct  dcel *)dcel_svc->open((void *)data, "r");
    }
    
    hsp->mapsvc = dcel_mapsvc;
    hap->svc = dcel_svc;
    //----------

    return hsp;
}



int
hiena_scanner_session_rewind(Hsp *scanner_session) {
    scanner_session->cur_location = 0;

    return 0;
}


int hsp_set_scanlib(Hsp *h, scanlib *slib)
{
    if(h == NULL)
    {
	return -1;
    }
    h->slib_ref = slib;
    return 0;
}


int hsp_set_scanner(Hsp *hsp, scannerserver *s)
{
    int err = 0;

    if(hsp == NULL)
    {
	return -1;
    }
    /* NO CLEANUP REQUIRED:
       hsp->scanner_ref is just a reference
       we can replace the pointer without cleanup
       if s is NULL this resets the pointer
     */
    hsp->scanner_ref = s;

    /* SETTING NULL SCANNER IS OK -- BUT POINTLESS */
    if(s == NULL)
    {
	return 0;
    }

    if(s->op == NULL)
    {
	/* then we can't initialize flex-bison session */
	return -2;
    }

    /* CLEANUP REQUIRED:
       however if hsp->lexer is NOT NULL
       we must clean it up before init'ing a new lexer.
     */
    if(hsp->lexer != NULL)
    {
	if(s->op->yylex_destroy != NULL)
	{
	    err = s->op->yylex_destroy(hsp->lexer);
	    if(err != 0)
	    {
		fprintf(stderr, "hiena:hsp.hsp_set_scanner: trouble destroying previous lexer, abort routine.\n");
		return -3;
	    }
	}
    }

    if(s->op->yylex_init_extra != NULL)
    {
	err = s->op->yylex_init_extra(hsp, &hsp->lexer);
	if(err != 0)
	{
	    perror("hiena:hsp.hsp_set_scanner");
	    fprintf(stderr, "hiena:hsp.hsp_set_scanner: can't initialize hsp, abort routine.\n");
	    return -4;
	}
    }

    /* set input to the FILE pointer "fp" */
    /* this SEEMS TO DUPLICATE EFFORTS of 'hsp_init_...' */
    /* also, does not contrain Hsp to NON-NULL 'fp' */
    /* need to ADD A VERIFICATION routine */
    if(hsp->dfh == NULL)
    {
	if(hsp->src_ref != NULL)
	{
	    hsp->dfh = dcel_svc->open(hsp->src_ref, "r"); 
	}else{
	    fprintf(stderr, "hiena:hsp.hsp_set_scanner: FILE fp and source are NULL, abort routine.\n");
	    return -5;
	}
    }
    printf("setting yyset_in...\n");
    if(s->op->yyset_in != NULL && s->op->yyget_in != NULL)
    {
	s->op->yyset_in(hsp->dfh, hsp->lexer);
	struct dcel_fh *fpcheck = s->op->yyget_in(hsp->lexer);

	if(hsp->dfh != fpcheck)
	{
	    fprintf(stderr, "hsp_set_scanner: setting lexer input stream failed, abort routine.\n");
	    return -6;
	}
    }else{
	fprintf(stderr,"hsp_set_scanner:yyset_in or yyget_in are NULL\n");
    }


    return 0;
}


Hsp *hsp_init_src_scanner_slib( Ppak *src_ref, scannerserver *s, scanlib *slib )
{
    Hsp *h

    h = new_hsp();
    if(h == NULL)
    {
        fprintf( stderr, "hsp_init_src_scanner_slib: can't create hsp, abort.\n");
        return NULL;
    }

/*
    h->parseroot = new_ppak(NULL);
    h->rq = new_rq();
    rq_set_hsp(h->rq,h);
*/

    h->svc = dcel_svc;
    h->mapsvc = dcel_mapsvc;


    h->src_ref = src_ref;

    if(src_ref != NULL)
    {
        h->dfh = dcel_svc->open(src_ref, "r");
    }
    hsp_set_scanner(h,s);
    hsp_set_scanlib(h,slib);

    return verify_hsp(h);
}
