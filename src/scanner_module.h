#ifndef HIENA_SCANNER_MODULE_H
#define HIENA_SCANNER_MODULE_H


#define YY_USER_ACTION yyextra->cur_location = yyextra->bytes_read;\
    yyextra->bytes_read += yyleng;


/*  #define YY_NO_INPUT  */


#define YY_INPUT(buf,result,max_size) \
    { \
    int c = yyextra->svc->getchar(yyextra->dfh); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }


#endif /* HIENA_SCANNER_MODULE_H */