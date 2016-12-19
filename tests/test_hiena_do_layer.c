#include <stdio.h>
#include "../src/hiena_do_layer.h"

int test_hiena_do_layer() {
	HEINA_DO_LAYER_T ret = NULL;

	void *arg1[] = { NULL };
	void *arg2[] = { NULL };

	int len1 = 1;
	int len2 = 1;

	int i,k;

	for(i=0;i<len1;i++) {
		for(k=0;k<len2;k++) {
			ret = hiena_do_layer( arg[i], arg[k] );
			if( hiena_do_layer_err( ret ) ) {
				fprintf(stderr, "test_hiena_do_layer: err\n");
			}
		}
	}
}
