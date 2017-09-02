%{
#include <stdlib.h>
#include "../../scanner_hdl.h"
#include "ox.tab.h"

#define TAB_TO_SPACE 8
#define YY_USER_ACTION yyextra->cur_location = yyextra->bytes_read;\
    yyextra->bytes_read += yyleng;

/*  #define YY_NO_INPUT  */

#define YY_INPUT(buf,result,max_size) \
    { \
    int c = yyextra->svc->getchar(yyextra->dfh); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
    }

static int get_indent_len(char *indent, int tabwidth) {
    int count = 0;
    char c;
    while ((c=indent[0])!='\0'){
	if (c == ' ')
	    count++;
	else if (c == '\t')
	    count+=tabwidth;
	indent++;
    }

    return count;
}


%}

%option reentrant stack bison-bridge noyywrap
%option bison-locations
%option extra-type="Hsp *"


LINE    ^[^ \t\n][^\n]*[\n]
INDENT  ^[ \t]+
INDENTED_LINE   [^ \t\n][^\n]*[\n]
BLANKLINE    ^([ \t]{-}[\n])*[\n]


%%
%{
int tab_to_space = TAB_TO_SPACE; 


/*
char *ttsa;
ttsa = yyextra->op->getenv("TAB_TO_SPACE");

int ttsi = 0;

if (ttsa != NULL) {
    ttsi = atoi(ttsa);
}

if (ttsi != 0) {
    tab_to_space = ttsi;
}
*/

/* LOCAL VARS */

void *b;  /* bounds */

%}

<<EOF>>				{
    return END;
				}

{LINE}		{

    yylval->ob = yyextra->op->newterm(yyextra->dfh, (void *)"LINE", yyextra->cur_location, yyleng);

    return LINE;
				}


{INDENT}				{

    yylval->ob = yyextra->op->newterm( yyextra->dfh, (void *)"INDENT", yyextra->cur_location, yyleng );

    return INDENT;
    				}

{INDENTED_LINE}	{

    yylval->ob = yyextra->op->newterm( yyextra->dfh, (void *)"INDENTED_LINE", yyextra->cur_location, yyleng );

    return INDENTED_LINE;
				}

{BLANKLINE}		{

    yylval->ob = yyextra->op->newterm( yyextra->dfh, (void *)"BLANKLINE", yyextra->cur_location, yyleng );

    return BLANKLINE;
				}


.				{ /* ignored */ }

%%

