#include <string.h>
#include <errno.h>
#include <stdlib.h>



#include "dcel.h"
#include "dcel_mapsvc.h"
#include "dcel_svc.h"
#include "hpat.h"
#include "hierr.h"
// #include "rql.h"
#include "scanner_hdl.h"




char *hsp_getenv(const char *envarname)
{
    return getenv(envarname);
}





/*== OBJECT IMPLEMENTATION: hiena scanner payload == */

Hsp *
hsp_new() {
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
    /*
    if(hsp->rq != NULL)
    {
        rq_cleanup(hsp->rq);
    }
    */

    if(hsp->lexer != NULL)
    {
	hsp->scanner_ref->op->yylex_destroy(hsp->lexer);
    }
    
    if(hsp->dfh != NULL)
    {
	dcel_svc_ops.close(hsp->dfh);
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
	/*

	*/
    if(
	    h->dfh	   == NULL ||
	    // h->rq          == NULL ||
	    // h->op          == NULL ||
       h->svc         == NULL ||
       h->mapsvc         == NULL ||
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

    Hsp *hsp = hsp_new();
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
        hsp->dfh = (struct dcel_fh *)dcel_svc_ops.open((void *)data, "r");
    }
    hsp->op = &dcel_mapsvc;
    hsp->mapsvc = &dcel_mapsvc;
    hsp->svc = &dcel_svc_ops;
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
	    int err = s->op->yylex_destroy(hsp->lexer);
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
	    hsp->dfh = (struct dcel_fh *)dcel_svc_ops.open(hsp->src_ref, "r"); 
	}else{
	    HIERR("hsp_set_scanner: dfh and source are NULL, abort routine.");
	    return -5;
	}
    }

    HIERR("hsp_set_scanner: setting yyset_in...");
    if(s->op->yyset_in != NULL && s->op->yyget_in != NULL)
    {
	s->op->yyset_in(NULL, hsp->lexer);
        //----------

/*
	struct dcel_fh *fpcheck = s->op->yyget_in(hsp->lexer);

	if(hsp->dfh != fpcheck)
	{
	    fprintf(stderr, "hsp_set_scanner: setting lexer input stream failed, abort routine.\n");
	    return -6;
	}
*/
    }else{
	fprintf(stderr,"hsp_set_scanner:yyset_in or yyget_in are NULL\n");
    }


    return 0;
}


Hsp *hsp_init_src_scanner_slib( Ppak *src_ref, scannerserver *s, scanlib *slib )
{
    Hsp *h;

    h = hsp_new();

    if(h == NULL)
    {
        HIERR("hsp_init_src_scanner_slib: can't create hsp, abort.");

        return NULL;
    }

    h->parseroot = dcel_new(NULL);

/*
    h->rq = new_rq();
    rq_set_hsp(h->rq,h);
*/

    h->svc = &dcel_svc_ops;
    h->mapsvc = &dcel_mapsvc;
    h->op = &dcel_mapsvc;
    h->src_ref = src_ref;

    if(src_ref != NULL)
    {
        h->dfh = dcel_svc_ops.open(src_ref, "r");
    }

    hsp_set_scanner(h,s);
    hsp_set_scanlib(h,slib);

    return verify_hsp(h);
}
