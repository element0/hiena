#ifndef _COSMOS_PATH_NODE_H_
#define _COSMOS_PATH_NODE_H_

#include "../access_frame.h"
#include "cosmos_id.h"

typedef struct access_frame cosmos_path_node_t;


cosmos_path_node_t *cosmos_path_node_new();

int cosmos_path_node_cleanup( cosmos_path_node_t * );

cosmos_path_node_t *cosmos_path_node_new_branch( cosmos_path_node_t *, cosmos_id_t );

cosmos_path_node_t *cosmos_path_node_get_branch( cosmos_path_node_t *, cosmos_id_t );

cosmos_path_node_t *cosmos_path_node_rm_branch( cosmos_path_node_t *, cosmos_id_t );

#endif /* !_COSMOS_PATH_NODE_H_ */
