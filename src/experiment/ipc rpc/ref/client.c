#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define SOCKFILEPATH "/var/local/gridhost/raygan/local"

int main( void )
{

	/* address */
	struct sockaddr_un sa;
	memset(&sa, 0, sizeof(struct sockaddr_un));

	sa.sun_family = AF_UNIX;
	snprintf(sa.sun_path, PATH_MAX, SOCKFILEPATH);


	/* open socket */
	int sfd;
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sfd == -1 )
	{
		printf("socket failed\n");
		return -1;
	}

	/* connect */

	if( connect(sfd, (struct sockaddr *) &sa,
				sizeof(struct sockaddr_un)) != 0 )
	{
		printf("connect failed.\n");
		return -1;
	}


	/* read and write */

	int n;
	char buf[256];

	n = snprintf(buf, 256, "bitch!");
	write( sfd, buf, n );

	n = read( sfd, buf, 256 );
	buf[n] = '\0';

	printf("incoming msg: %s\n", buf);

	close(sfd);
	
	return 0;
}
