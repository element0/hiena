#include <stdio.h>
#include "cosmos.h"


int main(int argc, char *argv[])
{
    struct cosmos *cm;

    cm = cosmos_db_new();




    cosmos_db_cleanup(cm);

    printf("libcosmos OK\n");
    
    return 0;
}