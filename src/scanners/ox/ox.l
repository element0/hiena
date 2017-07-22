%{
#include <stdlib.h>
#include "../../scanner_hdl.h"
#include "ox.tab.h"

#define TAB_TO_SPACE 8
#define YY_USER_ACTION yyextra->cur_location = yyextra->bytes_read;\
    yyextra->bytes_read += yyleng;

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

^[^ \t\n][^\n]*[\n]		{

    yylval->ob = yyextra->op->newterm(yyextra->dfh, LINE, yyextra->cur_location, yyleng);

    return LINE;
				}


^[ \t]+				{

    yylval->ob = yyextra->op->newterm( yyextra->dfh, INDENT, yyextra->cur_location, yyleng );

    return INDENT;
    				}

[^ \t\n][^\n]*[\n]		{

    yylval->ob = yyextra->op->newterm( yyextra->dfh, INDENTED_LINE, yyextra->cur_location, yyleng );

    return INDENTED_LINE;
				}

^([ \t]{-}[\n])*[\n]		{

    yylval->ob = yyextra->op->newterm( yyextra->dfh, BLANKLINE, yyextra->cur_location, yyleng );

    return BLANKLINE;
				}

.				{ /* ignored */ }

%%

