#ifndef _COSMOS_SERVER_CORE_H_
#define _COSMOS_SERVER_CORE_H_


struct cosmos_server_core {
    char *soc_path;
    char soc_addr_type;  /* u */
    int soc_addr_family; /*AF_UNIX*/
    int soc_type;  /* SOCK_STREAM */
    int soc_io_mode;     /*O_NONBLOCK */
    int soc_fd;
    int con_array_size;
    int con_count;
    int con_fd[];

    void *(*init)(int, char **);
    int (*cleanup)(void *);
    struct cosmos_server_msg *(*handle_msg)(void *, struct cosmos_server_msg *);

    struct cosmos_server_msg *(*rcvmsg)(void *, int);
    int (*sndmsg)(void *, struct cosmos_server_msg *);
};

int cosmos_server_core_init();




#endif /*! _COSMOS_SERVER_CORE_H_ */