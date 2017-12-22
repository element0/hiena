#include <stdio.h>
#include "cosmos_init.h"

static struct cosmos *db_init()
{
        struct cosmos *cm;
        int modc = 6;
        char *mod_path[] = {
  "/usr/lib/cosmos",
  "/usr/lib/cosmos/svc/file.so",
  "/usr/lib/cosmos/svc/dylib.so",
  "/usr/lib/cosmos/svc/ptr.so",
  "/usr/lib/cosmos/xformr/dcelcosm.so",
  "/usr/lib/cosmos/lookup/fudge.so",

        };

        cm = cosmos_init(modc, mod_path);

}


cosmos_id_t main(int argc, char *argv[])
{
        if(argc != 2)
        {
                printf("usage: cosmos FILEPATH\n");
                return 0;
        }
        struct cosmos *cm;
        cosmos_id_t ino;
        struct stat *stbuf;

        cm = db_init();

        ino = cosmos_lookup(cm, 0, argv[1]);

        return ino;
}
