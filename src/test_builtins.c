#include <stdlib.h>
#include <stdio.h>

#include "cosmos/cosmos_module.h"
#include "modules/file/file_builtin.h"



int main(int argc, char **argv)
{
    if( argc != 2 )
    {
        fprintf(stderr,"usage: %s Filename\n", argv[0]);
        return -1;
    }

    struct cosmos_module *mod;
    void *fp;

    mod = &cosmos_file_builtin;

    fp = mod->svc->open(argv[1], "r");
    mod->svc->close(fp);

    return 0;
}