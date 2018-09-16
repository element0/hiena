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


int make_socket(struct sockaddr *sa)
{
        int sfd;
        (struct sockaddr_un *)sa;

	/* socket address */
	unlink(SOCKFILEPATH);

        sa = malloc(sizeof(struct sockaddr_un));
	memset(sa, 0, sizeof(struct sockaddr_un));
	sa->sun_family = AF_UNIX;
	snprintf(sa->sun_path, PATH_MAX, SOCKFILEPATH);

	/* socket file descriptor */

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1 )
	{
		printf("socket failed.\n");
		return -1;
	}

	/* bind socket to address */

	if( bind(sfd, (struct sockaddr *)sa, sizeof(struct sockaddr_un)) != 0 )
	{
		printf("bind failed.\n");
		return -1;
	}
        return sfd;
}


int connect(int soc, struct sockaddr *sa)
{
        int con;
	socklen_t addr_len;

	/* listen for connection */

	if( listen(soc, 1) != 0 )
	{
		printf("listen failed.\n");
		return -1;
	}

	/* accept connection */

	con = accept(soc, (struct sockaddr *) &sa, &addr_len);

        return con;
}


int do_session(int con)
{
}


int main(int argc, char *argv[])
{
    int run = 1;

    struct sockaddr *sa;


    if(daemonize() == 1)
        return 0;

    if((soc = make_socket(sa)) == -1)
    {
        printf("server: err: make_socket() failed\n");
        return -1;
    }



    while(run == 1)
    {
        con = connect(soc, sa);
        do_session(con);
    }


    cleanup_socket(soc, sa);
    

    return 0;
}
