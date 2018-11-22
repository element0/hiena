
/*
this provides a generic socket server.
use for cosmosd and vm's.
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#include "cosmos_vfcall_reader.h"
#undef ns
#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(Cosmos, x)

#define c_vec_len(x) (sizeof(V)/sizeof((V)[0]))


/* returns file descriptor */

static int get_socket(const char *sockfpath)
{
    struct sockaddr_un sa;
    int sfd, cfd;
	/* socket address */

	unlink(sockfpath);

	memset(&sa, 0, sizeof(struct sockaddr_un));
	sa.sun_family = AF_UNIX;
	snprintf(sa.sun_path, PATH_MAX, sockfpath);


	/* socket file descriptor */

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);

	if(sfd == -1 )
	{
		printf("socket failed.\n");
		return -1;
	}


	/* bind socket to address */

	if( bind(sfd,(struct sockaddr *)&sa, sizeof(struct sockaddr_un)) != 0 )
	{
		printf("bind failed.\n");
		return -1;
	}


    return sfd;
}

inline int loop_iteration(int sfd, int cur_conn)
{
	int n;
   int bufmax = 256;
	uint8_t buf[bufmax];

	memset(buf, 0, bufmax);



    /* accept connection */

    if( listen(sfd, 1) != 0 )
    {
        printf("listen failed.\n");
        return -1;
    }

    cfd = accept(sfd, (struct sockaddr *) &sa, &addr_len);



    /* add connection to list */

    connection[0][0] = cfd;


    /* 


	/* read connection */

	n = read(cur_con, buf, bufmax);



	/* flatbuffers */
	ns(VFCall_table_t) vfcall = ns(VFCall_as_root(&buf));

	flatbuffers_string_t argvec = ns(VFCall_argv(vfcall));

	/*
	buf[n] = '\0';
	*/
	printf("incoming msg: %s\n", (const char *)argvec);

	/* write */
/*
	n = snprintf(buf, 256, "you bastard!");
	write(cfd, buf, n);
*/
}


int main_loop(const char *sockfpath) {

    struct sockaddr_un sa;
    int sfd, cfd;
    socklen_t addr_len;


    sfd = get_socket(sockfpath);


	/* get connections */

    while(server_run)
    {

        /* accept connection */

        if( listen(sfd, 1) != 0 )
        {
            printf("listen failed.\n");
            return -1;
        }


        cfd = accept(sfd, (struct sockaddr *) &sa, &addr_len);


	/* read */

	int n;
	uint8_t buf[256];
	memset(buf, 0, 256);

	n = read(cfd, buf, 256);


	/* flatbuffers */
	ns(VFCall_table_t) vfcall = ns(VFCall_as_root(&buf));

	flatbuffers_string_t argvec = ns(VFCall_argv(vfcall));

	/*
	buf[n] = '\0';
	*/
	printf("incoming msg: %s\n", (const char *)argvec);

	/* write */
/*
	n = snprintf(buf, 256, "you bastard!");
	write(cfd, buf, n);
*/
	/* wrap up */

	close( cfd );
	unlink(sockfpath);

	return 0;
}






