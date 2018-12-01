#ifndef _COSMOS_SERVER_MODULE_H_
#define _COSMOS_SERVER_MODULE_H_

void *server_module_init(int, char **);

int server_module_cleanup(void *);

struct cosmos_server_msg *server_module_handle_msg(void *, struct cosmos_server_msg *);


#endif /*!_COSMOS_SERVER_MODULE_H_*/