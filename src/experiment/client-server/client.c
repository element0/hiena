#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#include "idl/idl_builder.h"
#undef ns
#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(MyTest_Sample, x)

#define c_vec_len(x) (sizeof(V)/sizeof((V)[0]))

#define SOCKFILEPATH "/var/local/gridhost/raygan/local"



uint8_t *make_buffer(size_t *size)
{
	uint8_t *buf;

	flatcc_builder_t builder, *B;
	B = &builder;

	flatcc_builder_init(B);
	
	flatbuffers_string_ref_t s = flatbuffers_string_create_str(B, "bitch!");

	ns(VFCall_create_as_root(B, s));

	buf = flatcc_builder_finalize_buffer(B, size);


	return buf;
}



int main( void )
{
	/* buffer */
	size_t size;
	uint8_t *buf = make_buffer(&size);

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

	write( sfd, buf, size );

	/*
	n = read( sfd, buf, 256 );

	buf[n] = '\0';

	printf("incoming msg: %s\n", buf);
	*/

	close(sfd);

	free(buf);

	return 0;
}
