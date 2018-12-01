#include "cosmos_server_msg.h"


int vfcall_msg_unpack()
{
	/* flatbuffers */
	ns(VFCall_table_t) vfcall = ns(VFCall_as_root(&buf));

	flatbuffers_string_t argvec = ns(VFCall_argv(vfcall));

	/*
	buf[n] = '\0';
	*/
	printf("incoming msg: %s\n", (const char *)argvec);


    return 0;
}


int server_msg_receive(int *fd, struct cosmos_server_msg *dst, size_t *dst_size)
{
    if(dst == NULL)
    {
        HIERR("server_msg_receive: dst NULL");
        return -1;
    }

    
    size_t n;
    uint64_t len, msglen;
    uint64_t magicno = 0;


    len = sizeof(uint8_t)*8;


    n = read(fd, &magicno, len);
    if(n != 8)
    {
        HIERR("server_msg_receive: unexpected size when attempting to read magicno.");

        return -1;
    }

    if(magicno != cosmomsg_magic_num)
    {
        HIERR("server_msg_receive: magicno != cosmomsg_magic_num");
        fprintf(stderr, "server_msg_receive: magicno %ul != %ul\n", magicno, cosmomsg_magic_num);

        return -1;
    }


    len = sizeof(uint64_t);

    n = read(fd, &msglen, len);

    if(n != len || msglen == 0)
    {
        HIERR("server_msg_receive: cosmos msg hdr indicates 0 len msg");

        return -1;
    }

    /* read into buf */

    void *buf = NULL;
    buf = dst->buf;

    if(buf == NULL)
    {
        malloc(buf, msglen+1)
    }

    n = read(fd, buf, msglen);

    if(n != msglen)
    {
        HIERR("WARNING: server_msg_receive: message length different than what header declared");

    }


    return 0;
}