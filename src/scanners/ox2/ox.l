%option reentrant stack noyywrap
%option bison-bridge bison-locations
%option extra-type="Hsp *"


%{
#include <stdlib.h>
#include "../../scanner_hdl.h"
#include "../../scanner_module.h"
#include "ox.tab.h"


static int get_indent_len(char *indent, int tabwidth)
{
    int count = 0;
    char c;
    while ((c=indent[0])!='\0')
    {
        if (c == ' ')
            count++;
        else if (c == '\t')
            count+=tabwidth;
        indent++;
    }

    return count;
}
%}


%x OX
%x OUTLINE
%x IGNORE

BEGIN_FILE   ^
INDENT  ^[ \t]+
LINE    [^ \t\n][^\n]*[\n]
BLANKLINE    ^([ \t]{-}[\n])*[\n]


%%

%{
#define OX_MAX_DEPTH 64
int indent_stack[OX_MAX_DEPTH] = { 0,};
int cur_indent = 0;


int tab_to_space = 8; 
static int indent_spaces = 0;
char *ttsa = NULL;
int ttsi = 0;

ttsa = yyextra->op->getenv("TAB_TO_SPACE");

if (ttsa != NULL) {
    ttsi = atoi(ttsa);
}

if (ttsi != 0) {
    tab_to_space = ttsi;
}
%}


<INITIAL>{BEGIN_FILE}.   {

    yyless(0);

    BEGIN(OX);
    return BEGIN_OXFILE;
  }


<*><<EOF>>	{
    return END;
  }



<OUTLINE>{BLANKLINE}    {

    if( cur_indent > 0 )
    {
        cur_indent--;

        yyless(0);
        return END_BODY;
    }
    /* fall through */
  }


<*>{BLANKLINE}    {

/*
    yylval->ob = yyextra->op->newterm( yyextra->dfh, (void *)"BLANKLINE", yyextra->cur_location, yyleng );

*/

    BEGIN(IGNORE);
    return BLANKLINE;

  }

<OX>{INDENT}    {

    BEGIN(OUTLINE);

    /* fallthrough */
  }


<OUTLINE>{INDENT}	{


    indent_spaces = get_indent_len(yytext,tab_to_space);

    if( indent_spaces > indent_stack[cur_indent] )
    {
        cur_indent++;
        indent_stack[cur_indent] = indent_spaces;

        yyless(0);
        return START_BODY;
    }

    if( indent_spaces == indent_stack[cur_indent])
    {
/*
        yylval->ob = yyextra->op->newterm( yyextra->dfh, (void *)"INDENT", yyextra->cur_location, yyleng );

*/
        return START_ELEMENT;
    }

    if( indent_spaces < indent_stack[cur_indent] )
    {
        
        cur_indent--;

        yyless(0);
        return END_BODY;
    }

  }



<IGNORE>{LINE}    {

    BEGIN(OX);

    /* fall through */
  }


<OX,OUTLINE>{LINE}		{
/*
    yylval->ob = yyextra->op->newterm(yyextra->dfh, (void *)"LINE", yyextra->cur_location, yyleng);
*/
    return LINE;

  }



<IGNORE>{INDENT}{LINE}    {
/*
      yylval->ob = yyextra->op->newterm( yyextra->dfh, (void *)"FLOATING_LINE", yyextra->cur_location, yyleng );
*/

      return FLOATING_LINE;
  }



.    { /* ignored */ }

%%

