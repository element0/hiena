#ifndef HIENA_SCANNER_HANDLE_H
#define HIENA_SCANNER_HANDLE_H


#include <stdio.h>
#include "btrees.h"
#include "dcel.h"
#include "dcel_fh.h"
#include "dcel_dirent.h
#include "dcel_mapsvc.h"
#include "scanner.h"
#include "slib.h"
#include "rql.h"


typedef struct scanner_hdl Hsp;
typedef int Htok_t;
typedef struct hiena_dcel Ppak;
typedef void* yyscan_t;
typedef struct hiena_scanner scannerserver;
typedef struct hiena_slib scanlib;
typedef struct dcel_mapsvc_ops Hspops;


struct hiena_scanner_payload_callback_ops 
{
    /*-- MAPPING FUNCTIONS --*/

    struct hiena_dcel *(*make_ob)    (int tokid, Hsp *);

    	/* make_ob:  pass Hsp and yytext for bounds registration */

    int   (*set_bounds) (Ppak *, int axis, off_t offset, off_t len);

    void  (*set_buf)    (Ppak *, off_t len, void *buf);

    int   (*add_prop)   (Ppak *, Ppak *, Hsp *);
    int   (*add_child)  (Ppak *, Ppak *, Hsp *);
    int   (*merge_ob)   (Ppak *, Ppak *);


    void   (*putob) (Hsp *, int tokid, off_t len, char *);
    Htok_t (*gettok)(Hsp *);
    FILE  *(*fopen) (Ppak *, char *);
    
    char *(*getenv)(const char *);


    void (*set_rqtarg)(Hsp *, const char *);
    void (*set_rqdest)(Hsp *, const char *);
    void (*set_rqsrc) (Hsp *, Ppak *);
    void (*set_rqmap) (Hsp *, int);
    void (*set_rqop)  (Hsp *, int);

};


struct scanner_hdl
{
    /* result or garbage col */

    Ppak *parseroot;


    /* scanner state */

    yyscan_t       lexer;
    unsigned long int bytes_read;

    off_t cur_location;
    char *cur_tok_name;
    int   cur_tok_id;
    off_t cur_tok_start;
    off_t cur_tok_len;
    char *cur_tok_text;

    Ppak *last_added;
    Ppak *last_read;

    struct dcel_fh *dfh;
    FILE *fp;		/*:= !NULL */

    Hspops *op;		/*:= !NULL */
    struct hiena_svc *svc;
    struct dcel_mapsvc_ops *mapsvc; 

    rq *rq;		/*:= !NULL */			

    Ppak *src_ref;	/*:= !NULL */

    scannerserver *scanner_ref;	/*:= !NULL */

    scanlib *slib_ref;	/*:= !NULL */


    void *token_table;

    int    (*lex)   (void *,void *, Hsp *);

     /* void usu YYSTYPE, YYLTYPE 
     included from bison types */

    /* meta data */

    void *scandata;

};


int hsp_push_dirent(Hsp *, struct dcel_dirent *);


Hsp *hiena_scanner_payload_create();

void hiena_scanner_payload_cleanup(Hsp *);

int hsp_set_scanner(Hsp *, scannerserver *);

void hsp_rq_init(Hsp *, Ppak *);

Hsp *hsp_init(Ppak *);

Hsp *hsp_init_src_scanner_slib(Ppak *, scannerserver *, scanlib *);

int  hsp_set_scanlib(Hsp *, scanlib *);

void hsp_cleanup(Hsp *);




#endif /*! HIENA_SCANNER_HANDLE_H */
