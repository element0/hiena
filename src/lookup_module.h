


#ifndef _HIENA_LOOKUP_MODULE_H_
#define _HIENA_LOOKUP_MODULE_H_


#define YY_INPUT(buf,result,max_size) \
    { \
    static int pos = 0; \
    int c = yyextra->lookup_str[pos++]; \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }


int lookup_set_target( struct lookup_hdl *h, struct hiena_dcel *dc );

struct hiena_dcel *lookup_find_child( struct lookup_hdl *h, char *dc );

struct hiena_dcel *lookup_find_prop( struct lookup_hdl *h, char *dc );

struct hiena_dcel *lookup_grind( struct lookup_hdl *h, char *dc );


#endif /* ! _HIENA_LOOKUP_MODULE_H_ */