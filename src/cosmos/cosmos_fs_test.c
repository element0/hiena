#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "cosmos_db.h"
#include "cosmos_fs.h"
#include "../access_frame.h"


int main(int argc, char *argv[])
{
        if(argc!=2)
        {
                printf("usage: cosmos_fs_test FILENAME\n");
                return -1;
        }

        struct cosmos *cm;
        cosmos_id_t root, prev;
        cosmos_id_t node[3] = { NULL, NULL, NULL };
        char *d_name;
        int n;

        cm = cosmos_db_new();
        root = aframe_new();
        d_name = argv[1];

        prev = root;

        for(n = 0; n < 3; n++)
        {
                node[n] = cosmos_mknod(cm, prev, d_name, S_IFREG | S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH, 0);

                if(node[n] == NULL)
                {
                        break;
                }

                prev = node[n];
        }
        
        for(n = 0; n < 3; n++)
        {
                if(node[n] == NULL)
                {
                        break;
                }
                printf("node[%d]: %lu\n", n, (unsigned long)node[n]);
                aframe_cleanup(node[n]);
        }

        aframe_cleanup(root);
        cosmos_db_cleanup(cm);

        return 0;
}
