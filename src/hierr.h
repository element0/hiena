#ifndef HIERR
#include <stdio.h>
#define HIERR( es ) fprintf( stderr, "%s\n", es ), 1
#endif