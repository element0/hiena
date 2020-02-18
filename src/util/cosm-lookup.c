#include <stdio.h>
#include <stdlib.h>
#include "../cosmos/cosm_lookup.h"

static void print_usage(char *argv[])
{
	fprintf(stderr, "usage: %s [SUBPATH]\n", argv[0] ? argv[0] : NULL);
}

int main(int argc, char *argv[])
{
	char  *subpath;
	char  *result;

	argc > 2 ? print_usage(argv), exit(-1) : 1 ;
	subpath = argv[1] ? argv[1] : "";

	result = cosm_lookup(subpath);

	printf("%s\n", result);

	free(result);

	return 0;
}
