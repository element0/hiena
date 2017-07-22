#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hpat.h"
#include "ppak.h"
#include "sslib.h"
#include "rql.h"



/* WORKING */
void
scanlib_scan_ppak(Ppak *p, scanlib *slib){
    if(p==NULL || slib==NULL){
	fprintf(stderr,"scanlib_scan_ppak: ppak or scanlib can't be NULL, abort.\n");
	return;
    }
    Hsp *h = hsp_init(p);
    if(h == NULL){
	fprintf(stderr,"scanlib_scan_ppak: couldn't init Hsp, abort.\n");
    }
    scannerserver *ss = slib->newest; 
    while(ss != NULL) {
	if(hsp_set_scanner(h, ss) == -1)
	{
	    goto cleanup_and_return;
	}
	if(ss->op != NULL && ss->op->yyparse != NULL && h->lexer != NULL)
	{
	    ss->op->yyparse(h->lexer, h);
	}
        ss = ss->prev;
    }
cleanup_and_return:
    hsp_cleanup(h);
    return; 
}

Ppak *
ppak_lookup(Ppak *p, int m, Hpat *r, scanlib *slib) {
    printf("== WORKING: ppak_lookup() ==\n");
    if(slib == NULL){
	printf("ppak_lookup: scanlib can't be NULL, abort.\n");
	return NULL;
    }
    printf("Ppak *p:\n");
    if(m == RQCHILD){
	printf("searching child map...\n");
	
	// ------> PROBLEMS...

	if(p->first_child_posn == NULL)
	{
	    /* no child map OR scanner hasn't been activated */
	    /* APPLY SCANLIB TO PPAK */
	    scanlib_scan_ppak(p, slib);
	    if(p->first_child_posn == NULL)
	    {
		printf("after scanning, no children found.\n");
		return NULL;
	    }
	    
	}
    }else if(m == RQPROP){
	printf("searching property map...\n");
    }
    printf("\n");
    printf("--------\n");
    return NULL;
}


/*== OBJECT IMPLEMENTATION: request result set ==*/

rqres *new_rq_result() {
    rqres *rs = malloc(sizeof(rqres));
    if(rs!=NULL){
	memset(rs,0,sizeof(rqres));
    }
    return rs;
}

int rq_result_cleanup(rqres *rs) {
    if(rs != NULL)
    {
	if(rs->next != NULL)
	{
	    rq_result_cleanup(rs->next);
	}
	free(rs);
	rs = NULL;
	return 0;
    }
    return -1;
}

rqres *rq_result_add_ppak(rqres *rs, Ppak *p) {
    if(rs == NULL) {
	rs = new_rq_result();
    }
    if(rs->ent != NULL)
    {
	if(rs->next == NULL)
	{
	    rs->next = new_rq_result();
	}
	return rq_result_add_ppak(rs->next, p);
    }
    rs->ent = p;
    return rs;
}

rqres *rq_result_reset(rqres *rs) {
    if(rs == NULL) {
	return NULL;
    }
    if(rs->next != NULL){
	rq_result_cleanup(rs->next);
	rs->next = NULL;
    }
    rs->ent = NULL;

    return rs;
}




/*--------*/



/*== OBJECT IMPLEMENTATION: request ob ==*/
rq *new_rq() {
    rq *r = malloc(sizeof(rq));
    if(r!=NULL){
	memset(r,0,sizeof(rq));
    }
    return r;
}

int rq_cleanup(rq *rq) {
    if(rq != NULL)
    {
	if(rq->targ != NULL)
	{
	    hpat_cleanup(rq->targ);
	}
	if(rq->dest != NULL)
	{
	    hpat_cleanup(rq->dest);
	}
	if(rq->result != NULL)
	{
	    rq_result_cleanup(rq->result);
	}
    }
    free(rq);
    rq=NULL;
    return 0;
}

/* WORKING:
 * this function performs a lookup on the current result
 * and replaces the result with the lookup result.
 */
void set_targ(rq *r, Hpat *s) {
    if(r->targ!=NULL){
    	hpat_cleanup(r->targ);
    }
    fprintf(stderr,"libhiena:rql:set_targ %s\n",hpat_str_ptr(s));
    r->targ = s;

    /* lookup targ in map of result ppak */
    ppak_lookup(r->result->ent, r->map, s, r->hsp->slib_ref);


}

void set_dest(rq *r, Hpat *s) {
    if(r->dest!=NULL){
	
	hpat_cleanup(r->dest);
    }
    r->dest = s;
}

void set_src(rq *r, Ppak *s) {
    /* REMINDER: src should be a reference */
    r->src = s;
}

void set_map(rq *r, int whichmap) {
    r->map = whichmap;
}

void set_op(rq *r, int whichop) {
    r->op = whichop;
}

void set_res(rq *r, Ppak *p) {
    if(r == NULL){
	return;
    }
    if(r->result != NULL);
    rq_result_reset(r->result);
    r->result = rq_result_add_ppak(NULL, p);
}
void rq_set_hsp(rq *r, Hsp *h) {
    if(r == NULL){
	return;
    }
    r->hsp = h;
}
/*--------*/

/*== SUPPORT FUNCTIONS: for dealing with ppak and requests == */
Ppak *get_ppak_from_rqstr( Ppak *src, const char *rqstr, scanlib *slib)
{
    /*
       this function runs a "rqstr" on "src" datasource
       using "slib" scanner library to interpret rqstr.
       REQUIRES a "fudge" scannerserver in library.
       returns a Ppak pointer;
     */



    /* VALIDATE INPUT */
    if(src == NULL)
    {
	fprintf(stderr, "get_ppak_from_rqstr: src can't be NULL, abort routine.\n");
	return NULL;
    }
    if(rqstr == NULL)
    {
	fprintf(stderr, "get_ppak_from_rqstr: rqstr can't be NULL, abort routine.\n");
	return NULL;
    }
    if(slib == NULL)
    {
	fprintf(stderr, "get_ppak_from_rqstr: slib can't be NULL, abort routine.\n");
	return NULL;
    }


    /* INIT REQUEST HSP SCANNER SESSION */
    Ppak *rqpak = new_ppak_from_str(rqstr, NULL);
    if(rqpak == NULL)
    {
	fprintf(stderr, "get_ppak_from_rqstr: failed to packetize rqstr, abort routine.\n");
	return NULL;
    }
    /* this also opens a FILE pointer inside of the Hsp */
    Hsp *h = hsp_init(rqpak);
    if(h == NULL)
    {
	fprintf(stderr, "get_ppak_from_rqstr: can't init hsp, abort routine.\n");
	return NULL;
    }
    if(hsp_set_scanlib(h, slib) == -1)
    {
	fprintf(stderr, "get_ppak_from_rqstr: can't set hsp->scanlib, abort.\n");
	goto cleanup_and_return;
    }

    /* GET "fudge" SCANNER */
    scannerserver *s = get_scanner("fudge", slib);
    if(s == NULL)
    {
	fprintf(stderr, "get_ppak_from_rqstr: can't find \"fudge\" scannerserver, abort routine.\n");
	goto cleanup_and_return;
    }
    /* SET SCANNER, */
    /* ALSO SETS THE INPUT TO THE FILE POINTER */
    if(hsp_set_scanner(h, s) == -1)
    {
	goto cleanup_and_return;
    }

    /* INIT REQUEST */
    hsp_rq_init(h, src);
    /* this sets the current "result" to "src" */
    

    /* RUN THE SCANNER ON THE HSP */
    if(s->op != NULL && s->op->yyparse != NULL && h->lexer != NULL)
    {
	s->op->yyparse(h->lexer, h);
    }
    

cleanup_and_return:
    hsp_cleanup(h);
    return NULL;
}

/*--------*/
