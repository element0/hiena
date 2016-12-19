#include <stdlib.h>
#include "hiena_do_layer.h"


int hiena_do_layer_err( void *er ) {
	if( er == NULL ) {
		fprintf(stderr, "error: hiena_do_layer: output was NULL.\n");
		return 1;
	}
	switch(er->err) {
		case 1:
			fprintf(stderr, "error: hiena_do_layer: one or more inputs were null\n");
		default:
			fprintf(stderr, "error: hiena_do_layer: undefined error.");
	}
	return 1;
}


HIENA_DO_LAYER_T hiena_do_layer( void *dcel_io, void *modlist ) {
	HIENA_DO_LAYER_T er = malloc(sizeof(er));
	if( dcel_io == NULL || modlist == NULL ) {
		er->err = 1;
	}


	/*
	 *  clone input dcel
	 */

	HIENA_DO_LAYER_T retcel_io = dcel_io_clone( dcel_io );
	if ( dcel_io_clone_err( retcel_io ) ) {
		return er = NULL;
	}

	/*
	 *  select module to use on dcel based on dcel's `expect` property
	 */

	void * moduleid = dcel_io_get_expect( dcel_io );
	if ( dcel_io_get_expect_err( moduleid ) ) {
		er = NULL;
		goto abort_dcel;
	}
	void * mod = modlist_get_module( moduleid );
	if ( modlist_get_module_err( mod ) ) {
		er = NULL;
		goto abort_moduleid;
	}


	/*
	 *  run mapper on dcel
	 *  mapper is provided by module
	 */

	MAPERR_T maper_er = module_run_mapper( mod, retcel_io );
	if( module_run_mapper_err( maper_er ) ) {
		goto abort_moduleid;
	}

	/*
	 *  cleanup
	 */

	module_filterid_cleanup( filterid );
	dcel_io_moduleid_cleanup( moduleid );

	return retcel_io;

abort_moduelid:
	dcel_io_moduleid_cleanup( moduleid );
abort_dcel:
	dcel_io_cleanup( retcel_io );
	return er;
}
