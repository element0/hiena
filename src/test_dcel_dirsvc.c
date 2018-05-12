#include "dcel_dirh.h"
#include "dcel.h"
#include "dcel_child.h"
#include "dcel_dirsvc.h"

int main()
{
        struct hiena_dcel *dc, *dc2, *dc3, *dc4;
        struct dcel_dirh *dh;


        dc = dcel_new(NULL);
        dc2 = dcel_new(dc);
        dc3 = dcel_new(dc);

        dcel_add_child(dc, "wings", dc2, cm);

        dcel_add_child(dc, "beak", dc3, cm);


        dh = dcel_dirsvc.opendir(dc);


        while( 
        (e = dcel_dirsvc.readdir( dh ))
        != NULL))
        {
                dc4 = e->dcel;
                print("%lu\n",dc4);
        }

        dcel_dirsvc.closedir( dh );
        dcel_cleanup(dc);
}