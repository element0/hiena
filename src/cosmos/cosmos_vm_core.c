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

#define SOCKFILEPATH "/var/local/gridhost/raygan/local"


int main(void) {

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


	/* listen for connection */

	if( listen(sfd, 1) != 0 )
	{
		printf("listen failed.\n");
		return -1;
	}


	/* accept connection */

	socklen_t addr_len;
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
	unlink(SOCKFILEPATH);

	return 0;
}



