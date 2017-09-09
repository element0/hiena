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

BEGIN_FILE   ^(.|[\n])
BLANKLINE    ^([ \t]{-}[\n])*[\n]
INDENT  ^[ \t]+
LINE    [^ \t\n][^\n]*[\n]
NOINDENTLINE    ^[^ \t\n][^\n]*[\n]



%%

%{
#define OX_MAX_DEPTH 64

static int indent_stack[OX_MAX_DEPTH] = { 0,};
static int cur_indent = 0;
static int indent_spaces = 0;

static int tab_to_space = 8;
char *ttsa = NULL;
int ttsi = 0;

ttsa = NULL;  // yyextra->op->getenv("TAB_TO_SPACE");

if (ttsa != NULL) {
    ttsi = atoi(ttsa);
}

if (ttsi != 0) {
    tab_to_space = ttsi;
}
%}


<INITIAL>{BEGIN_FILE}   {

    yyless(0);
    yy_set_bol(1);

    OXPRINT("BEGIN_OXFILE\n");

    BEGIN(OX);
    return BEGIN_OXFILE;
  }


<*><<EOF>>	{

    OXPRINT("END\n");

    return END;
  }


<OX>{BLANKLINE}    {

    OXPRINT("BLANKLINE, BEGIN(IGNORE)\n");

    BEGIN(IGNORE);

    return BLANKLINE;
  }


<OX,OUTLINE>{LINE}		{

    OXPRINT("LINE\n");

    return LINE;
  }

<OX,OUTLINE>{INDENT}	{

    OXPRINT("INDENT, BEGIN(OUTLINE)\n");
    BEGIN(OUTLINE);

    indent_spaces = get_indent_len(yytext,tab_to_space);

    if( indent_spaces > indent_stack[cur_indent] )
    {
        if( cur_indent == OX_MAX_DEPTH )
        {
                fprintf(stderr,"ox err: cur_indent at max.");
                fflush(stderr);
                return END;
        }
        cur_indent++;

        indent_stack[cur_indent] = indent_spaces;


        OXPRINT("START_BODY\n");


        yyless(0);
        yy_set_bol(1);

        return START_BODY;
    }

    if( indent_spaces == indent_stack[cur_indent])
    {

        OXPRINT("START_ELEMENT\n");


        return START_ELEMENT;
    }

    if( indent_spaces < indent_stack[cur_indent] )
    {
        
        cur_indent--;


        OXPRINT("END_BODY\n");

        yyless(0);
        yy_set_bol(1);

        return END_BODY;
    }

  }




<OUTLINE>{BLANKLINE}    {

    if( cur_indent > 0 )
    {
        cur_indent--;

        OXPRINT("END_BODY\n");

        yyless(0);
        yy_set_bol(1);

        return END_BODY;
    }

    OXPRINT("BLANKLINE, BEGIN(IGNORE)\n");

    BEGIN(IGNORE);

    return BLANKLINE;
  }


<IGNORE>{BLANKLINE}    {
    OXPRINT("BLANKLINE (IGNORE)\n");

    return BLANKLINE;
  }


<IGNORE>{INDENT}{LINE}    {

    OXPRINT("FLOATING_LINE, (IGNORE)\n");

    return FLOATING_LINE;
  }


<IGNORE>{NOINDENTLINE}    {

    BEGIN(OX);
    OXPRINT("LINE, BEGIN(OX)\n");

    return LINE;
  }


.    {

    OXPRINT("Unrecognized character, sweeping under the rug.\n");

  }

%%

