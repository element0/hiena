
#define HIENA_DO_LAYER_T struct hiena_do_layer_tempval *
#define HIENA_DO_LAYER_ARG1_T void *
#define HIENA_DO_LAYER_ARG2_T void *

struct hiena_do_layer_tempval {
	int err;
};

void * dcel_io_clone( void * );
int    dcel_io_clone_err( void * );

int hiena_do_layer_err( HIENA_DO_LAYER_T );

HIENA_DO_LAYER_T hiena_do_layer( void *, void *);
