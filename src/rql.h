



#ifndef _HIENA_RQL_H_
#define _HIENA_RQL_H_

#include "hpat.h"
#include "dcel.h"
#include "scanner_hdl.h"

typedef struct hiena_request rq;
typedef struct hiena_rq_ops rqops;
typedef struct hiena_dcel Ppak;
typedef struct hiena_rq_result_entry rqres;
typedef struct scanner_hdl Hsp;


struct hiena_rq_result_entry {
    rqres *next;
    Ppak  *ent;
};

enum rq_maptype { RQCHILD, RQPROP };
enum rq_optype  { RQMATCH, RQASSIGN };


struct hiena_request {
    Hsp *hsp;

    /* PREVIOUS IMPLEMENTATION */
    int map;    /* map selector := property | child */

    int op;  	/* operation    := match | assign */

    Hpat *targ;
    Hpat *dest;
    Ppak *src;	/* maybe replace with cur_src_ref */

    rqres *result;
    rqres *result_tail;

    /* result keeps current list of selection */


    /* NEW IMPLEMENTATION */
    int map_selector;
    int op_selector;
    Ppak *cur_targ_ref;
    Ppak *cur_dest_ref;
    Ppak *cur_src_ref;

    /* result map belongs to request ppak */
    

};



rq   *new_rq();
int  rq_cleanup(rq *);
void set_targ(rq *, Hpat *);
void set_dest(rq *, Hpat *);
void set_src (rq *, Ppak *);
void set_map (rq *, int);
void set_op  (rq *, int);
void set_res (rq *, Ppak *);
void rq_set_hsp(rq *, Hsp *);




#endif /*!_HIENA_RQL_H_*/

