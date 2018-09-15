#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define SOCKFILEPATH "./testsock"

int daemonize()
{
    return 0;
}


int make_socket()
{
	/* socket address */

	struct sockaddr_un sa;

	unlink(SOCKFILEPATH);

	memset(&sa, 0, sizeof(struct sockaddr_un));
	sa.sun_family = AF_UNIX;
	snprintf(sa.sun_path, PATH_MAX, SOCKFILEPATH);

	/* socket file descriptor */

	int sfd, cfd;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1 )
	{
		printf("socket failed.\n");
		return -1;
	}

	/* bind socket to address */

	if( bind(sfd, (struct sockaddr *)&sa,
				sizeof(struct sockaddr_un)) != 0 )
	{
		printf("bind failed.\n");
		return -1;
	}
        return 0;
}


int connect()
{
	/* listen for connection */

	if( listen(sfd, 1) != 0 )
	{
		printf("listen failed.\n");
		return -1;
	}

	/* accept connection */

	socklen_t addr_len;
	cfd = accept(sfd, (struct sockaddr *) &sa, &addr_len);

        return cfd;
}


int do_session()
{
}


int main(int argc, char *argv[])
{
    int run = 1


    if(daemonize() == 1)
        return 0;

    if(make_socket() == -1)
    {
        printf("server: err: make_socket() failed\n");
        return -1;
    }



    while(run == 1)
    {
        cfd = connect();
        do_session();
    }


    cleanup_socket();
    

    return 0;
}
