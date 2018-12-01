#ifndef _COSMOS_SERVER_MSG_H_
#define _COSMOS_SERVER_MSG_H_


#include "cosmos_server_msg/vfncall_reader.h"

#undef ns

#define ns(x) FLATBUFFERS_WRAP_NAMESPACE(Cosmos, x)

#define c_vec_len(x) (sizeof(V)/sizeof((V)[0]))


uint64_t cosmomsg_magic_num = (uint64_t)(*"cosmomsg");


struct cosmos_server_msg {
    int fd;
    void *buf;
    size_t len;
};


struct cosmos_server_msg *server_msg_receive(void *, int);

int server_msg_send(void *, struct cosmos_server_msg *);




#ifndef /*! _COSMOS_SERVER_MSG_H_ */