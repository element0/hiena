%code requires {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../scanner_hdl.h"
#include "../../mapcel.h"

typedef void* yyscan_t;


#define OXPRINT(s) \
    printf(s);\
    fflush(stdout);

}

%define lr.type ielr
%define api.pure //full
%locations
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%parse-param {Hsp *hsp}

/* get token name via yytname[i] */
%token-table

%union {
    int   len;
    char *str;
    struct hiena_mapcel *ob;
}


%token <ob> INDENT
%token <ob> LINE
%token <ob> BLANKLINE
%token <ob> FLOATING_LINE
%token BEGIN_OXFILE
%token END
%token START_BODY
%token END_BODY
%token START_ELEMENT

%type <ob> outline outline_block
%type <ob> outline_body
%type <ob> ox_file_head
%type <ob> ox_file_body
%type <ob> blank_or_indented_lines

/*
%destructor { free($$); } <str>
%destructor { mapcel_cleanup($$); } <ob>
*/


%{
    int num_ox = 0;
    int prev_indent = 0;
    void *ruleid;

%}

%%

ox_good
   : ox_file
    {
        OXPRINT("\n");
        OXPRINT("ox good.\n");
        return;
    }
   ;

ox_file
   : ox_file_head
     ox_file_body
     ox_file_tail
    {
        OXPRINT("ox_file\n");
    }
   ;

ox_file_head
   : BEGIN_OXFILE
   {
        OXPRINT("parser: BEGIN_OXFILE\n");
   }
   | BEGIN_OXFILE
     blank_or_indented_lines
   {
    OXPRINT("parser: BEGIN_OXFILE\n");
    OXPRINT("parser: blank_or_indented_lines\n");
    
   }
   ;


ox_file_tail
   : blank_or_indented_lines
     END
   | END
   ;


ox_file_body
	: outline_block
	{

	}

	| ox_file_body
	  blank_or_indented_lines
	  outline_block
	{

	}
   ;


outline_block	
	: outline
	{
      
	}

	| outline_block
	  outline
	{

	}
	;


outline
	: LINE
	{
       
	}

   | LINE
     START_BODY
     outline_body
     END_BODY
   {
       
	}
	;



outline_body
   : START_ELEMENT outline
   {
       
   }

   | outline_body
     START_ELEMENT outline
   {

   }
   ;


blank_or_indented_lines
   : BLANKLINE
   {
       
   }

   | FLOATING_LINE

   | blank_or_indented_lines
     BLANKLINE

   | blank_or_indented_lines
     FLOATING_LINE
   ;



%%
struct hiena_scanner sslookup = {
    .allowed_child_scanners = { "ulang" }	/* {:: ulang ::} */
};


char **show_allowed_child_scanners() {
    return sslookup.allowed_child_scanners;
}

const char *get_tok_name(int tokid) {
    return yytname[tokid-256+1];
}



/* leave return type blank
 *  - bison caveat
 */
yyerror(char const *s)
{
    fprintf(stderr, "ox2.so err: %s\n", s);
}

int hiena_scannerop_parse(Hsp *hsp)
{
    yyscan_t scanner;
    yylex_init_extra( hsp, &scanner );

    yyset_in( NULL, scanner );
    
    yyparse(scanner, hsp);

    yylex_destroy(scanner);

    return 0;
}

/* FOR TESTING */
/*
int main()
{
    FILE *fp = stdin;
    Hsp  *payload = NULL;
    hiena_scannerop_parse(fp, payload);
}
*/
