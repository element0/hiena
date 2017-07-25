#ifndef HIENA_SCANNER_SVC_H
#define HIENA_SCANNER_SVC_H

#include "scanner_hdl.h"

#define HIENA_SCANNER_SVC_OPS_COUNT 8

struct scanner_svc_ops {

    int (*parse)(Hsp *);

    char **(*show_allowed_child_scanners)();

    char *(*get_tok_name)(int);

    int (*yyparse)(yyscan_t *, Hsp *);
    int (*yylex_init_extra)(Hsp *, yyscan_t *);
    int (*yylex_destroy)(yyscan_t *);
    void (*yyset_in)(struct dcel_fh *, yyscan_t *);
    struct dcel_fh *(*yyget_in)(yyscan_t *);
};

struct scanner_svc_ops scanner_svc;

#endif /* !HIENA_SCANNER_SVC_H */
