#include <stdlib.h>

void * dcel_io_clone( void * );
int    dcel_io_clone_err( void * );



void *hiena( void *dcel_io, void *modlist ) {

	void *er = NULL;

	/*
	 *  clone input dcel
	 */

	void * retcel_io = dcel_io_clone( dcel_io );
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
