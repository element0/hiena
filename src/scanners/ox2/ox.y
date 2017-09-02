%code requires {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../scanner_hdl.h"
#include "../../mapcel.h"

typedef void* yyscan_t;

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
%type <ob> ox_file_body

%destructor { free($$); } <str>
%destructor { mapcel_cleanup($$); } <ob>

%{
    int num_ox = 0;
    int prev_indent = 0;
    void *ruleid;
%}

%%

ox_good
   : ox_file
    {
        printf("\n");
        printf("ox good.\n");
        return;
    }
   ;

ox_file
   : ox_file_head
     ox_file_body
     ox_file_tail
    {
        printf("ox_file\n");
    }
   ;

ox_file_head
   : BEGIN_OXFILE
   | BEGIN_OXFILE
     blank_or_indented_lines
   ;


ox_file_tail
   : blank_or_indented_lines
     END
   | END
   ;


ox_file_body
	: outline_block
	{
/*
       ruleid = (void *) "ox_file_body";

		$$ = hsp->op->new(ruleid);

        hsp->op->add($$, $1);
        hsp->op->new_dirent(hsp->dfh, $1);

        hsp->op->new_dir(hsp->dfh, $$);
*/
	}

	| ox_file_body
	  blank_or_indented_lines
	  outline_block
	{
/*
		hsp->op->add($$, $1);
       hsp->op->new_dirent(hsp->dfh, $3);
*/
	}
   ;


outline_block	
	: outline
	{
       ruleid = (void *)"outline_block";
/*
		$$ = hsp->op->new(ruleid);
		hsp->op->add($$,$1);
		hsp->op->new_dirent(hsp->dfh, $1);
*/
	}

	| outline_block
	  outline
	{
/*
		hsp->op->add($$,$2);
		hsp->op->new_dirent(hsp->dfh, $2);
*/
	}
	;


outline
	: LINE
	{
       ruleid = (void *)"outline";
/*
		$$ = hsp->op->new(ruleid);
       hsp->op->add($$, $1);
*/
	}

   | LINE
     START_BODY
     outline_body
     END_BODY
   {
       ruleid = (void *)"outline";
/*
		$$ = hsp->op->new(ruleid);
       hsp->op->add($$, $1);
       hsp->op->add($$, $3);
		hsp->op->new_dirent(hsp->dfh, $$);
*/
	}
	;



outline_body
   : START_ELEMENT outline
   {
       ruleid = (void *)"outline_body";
		// $$ = hsp->op->new(ruleid);
       // hsp->op->add($$, $2);
   }

   | outline_body
     START_ELEMENT outline
   {
       // hsp->op->add($$, $3);
   }
   ;


blank_or_indented_lines
   : BLANKLINE

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
    fprintf(stderr, "ox.ss err: %s\n", s);
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
