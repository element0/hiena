#ifndef _COSMOS_MODULE_H_
#define _COSMOS_MODULE_H_

#include "../access_frame.h"
#include "../dcel.h"
#include "../cosmos.h"
#include "../hiena_svc.h"
#include "../scanner_hdl.h"



struct hiena_dcel *cosmos_source_fn( struct access_frame *af, int argc, void **argv, struct cosmos *);


char *cosmos_calc_fnpath(cm, targ, modname, "cosmos_map_fn");


struct cosmos_module {
        
        /* producers */
        struct hiena_dcel *(*source)(struct access_frame *af, int argc, void **argv, struct cosmos *);

        struct hiena_dcel *(*map)(struct access_frame *af, int argc, void **argv, struct cosmos *);

        struct hiena_dcel *(*transform)(struct access_frame *af, int argc, void **argv, struct cosmos *);


        /* service */
        struct hiena_service *service;

        /* scanner */
        int (*scannerop_parse)(Hsp *hsp);
};


#endif  /*! _COSMOS_MODULE_H_ */