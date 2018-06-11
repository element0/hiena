#ifndef COSMOS_EXEC_H
#define COSMOS_EXEC_H

cosmos_id_t cosmos_exec(struct cosmos *, cosmos_id_t af, cosmos_id_t fn, int argc, void *argv);

cosmos_id_t cosmos_exec_mapfn(struct cosmos *, cosmos_id_t af, cosmos_id_t fn);


#endif /*! COSMOS_EXEC_H */