#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define SOCKFILEPATH "./testsock"

typedef struct connection {
    int fd;
    struct sockaddr_un sa;
    socklen_t addr_len;
}con_t;

int daemonize()
{
    return 0;
}


int make_socket()
{
        int sfd;
        struct sockaddr_un sa;

	/* socket address */
	unlink(SOCKFILEPATH);

	memset(&sa, 0, sizeof(struct sockaddr_un));
	sa.sun_family = AF_UNIX;
	snprintf(sa.sun_path, PATH_MAX, SOCKFILEPATH);

	/* socket file descriptor */

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1 )
	{
		printf("socket failed.\n");
		return -1;
	}

	/* bind socket to address */

	if( bind(sfd, (struct sockaddr *)&sa, sizeof(struct sockaddr_un)) != 0 )
	{
		printf("bind failed.\n");
		return -1;
	}

        return sfd;
}


con_t *do_connect(int soc)
{
    con_t *con = malloc(sizeof(*con));


	/* listen for connection */

	if( listen(soc, 1) != 0 )
	{
		printf("listen failed.\n");
		return NULL;
	}

	/* accept connection */

    con->fd = accept(soc, (struct sockaddr *)&(con->sa), &(con->addr_len));

    return con;
}


int do_session(con_t *con)
{
    char *c;
    FILE *fp;
    int i, len;
    int op, x, y, res;


    // recv
    fp = fdopen(con->fd, "r");

    len = fgetc(fp);

    c = malloc((sizeof(char)*len)+1);

    for(i=1; i<len; i++)
    {
        c[i] = fgetc(fp);
    }
    c[i] = '\0';

    fclose(fp);

    op = c[1];
    x  = c[2];
    y  = c[3];

    printf("server: op %c x %d y %d\n");

    if(op == '+')
    {
        res = x + y;
    }else if(op == '-'){
        res = x - y;
    }

    // send
    send(con->fd, &res, sizeof(res), 0);


    return 0;
}

void close_connection(con_t *con)
{
    close(con->fd);
    free(con);
}


int main(int argc, char *argv[])
{
    int soc, run = 1;

    con_t *con;


    if(daemonize() == 1)
        return 0;

    if((soc = make_socket()) == -1)
    {
        printf("server: err: make_socket() failed\n");
        return -1;
    }



    while(run == 1)
    {
        con = do_connect(soc);
        do_session(con);
        close_connection(con);
    }


    close(soc);
    

    return 0;
}
