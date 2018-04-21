
#ifndef _HIENA_LOOKUP_MODULE_H_
#define _HIENA_LOOKUP_MODULE_H_

#define YY_INPUT(buf,result,max_size) \
    { \
    static int pos = 0; \
    int c = yyextra->lookup_str[pos++]; \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }


struct lookup_hdl *lookup_module_init( struct hiena_dcel *dc, struct hiena_slib *slib );


#endif /* ! _HIENA_LOOKUP_MODULE_H_ */
