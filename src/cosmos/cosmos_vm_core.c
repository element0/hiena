#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#include "cosmos_server_core.h"

/* cosmos_server_msg defines a function which reads a cosmos message from a file descriptor and puts it into a buffer.

   tbd: buf malloc'd by caller?

 */
#include "cosmos_server_msg.h"
#include "cosmos_server_module.h"



int main(int argc, char *argc[])
{

    if(argc != 2)
    {
        printf("usage: cmd SOCKETFILEPATH\n");
        exit -1;
    }


    struct cosmos_server_core csc =
    {
        .soc_path = argc[1];
        .init = server_module_init;
        .cleanup = server_module_cleanup;
        .handle_msg = server_module_handle_message;
        .rcvmsg = server_msg_receive;
        .sndmsg = server_msg_send;
    };


    struct cosmos_vm_core vm;


    er = cosmos_server_core(&csc);



    

	/* wrap up */

	close( cfd );
	unlink(SOCKFILEPATH);

	return 0;
}



