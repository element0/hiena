#include <stdio.h>

#include "test_hiena_do_layer.h"

int main() {
	if( test_hiena_do_layer() == -1 ) {
		fprintf(stderr, "test_hiena_do_layer(); failed.\n");
	}
}
