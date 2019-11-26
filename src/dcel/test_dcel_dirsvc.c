#include <stdio.h>
#include "dcel.h"
#include "dcel_dirh.h"
#include "dcel_dirsvc.h"
#include "dcel_dirent.h"
#include "cosmos.h"

int main()
{
        struct hiena_dcel *dc, *dc2, *dc3, *dc4;
        struct dcel_dirh *dh;
        struct cosmos *cm;
        struct dcel_dirent *e;


        dc = dcel_new(NULL);
        dc2 = dcel_new(dc);
        dc3 = dcel_new(dc);
        dc4 = NULL;
        dh = NULL;
        cm = cosmos_db_new();
        e = NULL;


        dcel_add_child(dc, "wings", dc2, cm);
        dcel_add_child(dc, "beak", dc3, cm);
        dh = dcel_dirsvc.opendir(dc);


        while((e = dcel_dirsvc.readdir( dh )) != NULL)
        {
                dc4 = e->dcel;
                printf("%lu\n",dc4);
        }

        dcel_dirsvc.closedir( dh );
        dcel_cleanup(dc);

        cosmos_db_cleanup( cm );

        return 0;
}
