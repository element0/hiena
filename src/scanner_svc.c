/*== IMPLEMENTATION: scannerserver ==*/

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "scanner.h"
#include "scanner_hdl.h"

scannerserver *hiena_scanner_create() {
    size_t size         = sizeof(scannerserver);
    scannerserver *scanner = malloc(size);
    if(scanner == NULL)
    {
	fprintf(stderr, "hiena_scanner_create: failed to allocate memory for scannerserver, abort routine.\n");
	return NULL;
    }
    memset(scanner, 0, size);

    scanner->op = malloc(sizeof(struct scanner_svc_ops));

    return scanner;
}

void hiena_scanner_cleanup(scannerserver *scanner) {
    if(scanner==NULL){
	fprintf(stderr,"hiena:scanner_system:trying to cleanup NULL scanner\n");
	return;
    }
    if(scanner->dl!=NULL){
	char *dlerr=NULL;//dlerror();
	if(dlclose(scanner->dl)!=0){
	    fprintf(stderr,"hiena_scanner_cleanup dlclose err :%s\n",dlerr);	
	}
    }
    free(scanner->name);
    free(scanner->op);
    free(scanner);
}

/******* TODO ****************/
/* use struct hiena_scannerlib_entry instead of scannerserver */
/* using slib_entry structure will implicity include a link to slib, so
   we can thenceforth remove 'slib' from these arguments. */


void do_scanner(scannerserver *s, Ppak *p, scanlib *slib) {
    if(s == NULL || p == NULL) {
	fprintf(stderr, "do_scanner: NULL scanner or Ppak, abort.\n");
	return;
    }
    Hsp *h = hsp_init_src_scanner_slib(p,s,slib);
    if(h == NULL)
    {
	fprintf(stderr, "do_scanner: can't init Hsp, abort.\n");
	return;
    }

    if((s->op != NULL) && (s->op->yyparse != NULL) && (h->lexer != NULL))
    {
	printf("do_scanner: %s, running scanner...\n", s->name);
	s->op->yyparse(h->lexer, h);
	printf("do_scanner: %s, done.\n", s->name);
    }else{
	fprintf(stderr, "do_scanner: s->op == %lu\n",
		(long unsigned int)s->op);
	fprintf(stderr, "do_scanner: s->op->yyparse == %lu\n",
		(long unsigned int)s->op->yyparse);
	fprintf(stderr, "do_scanner: h->lexer == %lu\n",
		(long unsigned int)h->lexer);
    }

    hsp_cleanup(h);
    return;
}
void
do_scanners(Ppak *p, scanlib *slib) {
    /*
       for each scanner in slib
       do
           scanner( p )
       done
       */
    scannerserver *s = slib_get_next_scanner(slib, NULL);
    while(s != NULL) {
	// TODO: multi-threaded version
	do_scanner(s, p, slib);
	s = slib_get_next_scanner(slib, s);
    }

    return;
}


/*--------*/

