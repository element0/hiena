#include "hiena_fh.h"

void main( )
{
        struct hiena_fh hfs;
        struct hiena_svc hsvc;

        hfs.ops = &hsvc;
}