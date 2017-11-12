#ifndef COSMOS_DAEMON_H
#define COSMOS_DAEMON_H

#include "../hiena.h"

#define tbd_t void


struct cosmos_daemon {
        tbd_t *user;
        struct hiena_dcel *cosm;
        struct hiena_slib *scanners;
        tbd_t *strings;
};


#endif /* !COSMOS_DAEMON_H */