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
%token <ob> BEGIN_OXFILE
%token <ob> END
%token <ob> START_BODY
%token <ob> END_BODY
%token <ob> START_ELEMENT

%type <ob> ox_file ox_file_head ox_file_body ox_file_tail

%type <ob> outline_block outline outline_body start_body_action

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

        OXPRINT("op finish\n");
        hsp->op->finish(hsp->dfh,$1);

        return;
    }
   ;

ox_file
   : ox_file_head
     ox_file_body
     ox_file_tail
    {
        OXPRINT("ox_file\n");

        $$ = hsp->op->new((void *)"ox_file");
        hsp->op->add($$,$1);
        hsp->op->add($$,$2);
        hsp->op->add($$,$3);

        OXPRINT("op finish dir\n");
        hsp->op->finish_dir(hsp->dfh, $$);
    }
   ;

ox_file_head
   : BEGIN_OXFILE
   {
        OXPRINT("parser: BEGIN_OXFILE\n");

        $$ = hsp->op->new((void *)"ox_file_head");

   }
   | BEGIN_OXFILE
     blank_or_indented_lines
   {
    OXPRINT("parser: BEGIN_OXFILE\n");
    OXPRINT("parser: blank_or_indented_lines\n");

        $$ = hsp->op->new((void *)"ox_file_head");
        hsp->op->add($$,$1);
   }
   ;


ox_file_tail
   : blank_or_indented_lines
     END
   {
        $$ = hsp->op->new((void *)"ox_file_tail");
        hsp->op->add($$,$1);
   }
   | END
   {
        $$ = hsp->op->new((void *)"ox_file_tail");
   }
   ;


ox_file_body
	: outline_block
	{
        $$ = hsp->op->new((void *)"ox_file_body");
        hsp->op->add($$,$1);

        OXPRINT("op finish dir\n");
        hsp->op->finish_dir(hsp->dfh, $1);

        OXPRINT("op new dirent\n");
        hsp->op->new_dirent(hsp->dfh, $1);
	}

	| ox_file_body
	  blank_or_indented_lines
	  outline_block
	{
        hsp->op->add($1,$2);
        hsp->op->add($1,$3);

        OXPRINT("op finish dir\n");
        hsp->op->finish_dir(hsp->dfh, $3);
        OXPRINT("op new dirent\n");
        hsp->op->new_dirent(hsp->dfh, $3);
	}
   ;


outline_block	
	: outline
	{
        $$ = hsp->op->new((void *)"outline_block");
        hsp->op->add($$,$1);

        OXPRINT("op new dirent\n");

        hsp->op->new_dirent(hsp->dfh, $1 );
	}

	| outline_block
	  outline
	{
        hsp->op->add($1,$2);

        OXPRINT("op new dirent\n");

        hsp->op->new_dirent(hsp->dfh, $2 );
	}
	;


outline
	: LINE
	{
        $$ = hsp->op->new((void *)"outline");
        hsp->op->add($$,$1);
	}

   | LINE
     start_body_action
     outline_body
     END_BODY
   {
        $$ = hsp->op->new((void *)"outline");
        hsp->op->add($$,$1);
        hsp->op->add($$,$2);
        hsp->op->add($$,$3);
        hsp->op->add($$,$4);

        OXPRINT("op finish dir\n");

        hsp->op->finish_dir(hsp->dfh, $$);
	}
	;

start_body_action
   : START_BODY
   {
        $$ = $1;

        OXPRINT("op start dir\n");

        hsp->op->start_dir(hsp->dfh);
   }
   ;

outline_body
   : START_ELEMENT outline
   {
        $$ = hsp->op->new((void *)"outline_body");
        hsp->op->add($$,$1);
        hsp->op->add($$,$2);

        OXPRINT("op new dirent\n");

        hsp->op->new_dirent(hsp->dfh, $2);
   }

   | outline_body
     START_ELEMENT outline
   {
        hsp->op->add($1,$2);
        hsp->op->add($1,$3);

        OXPRINT("op new dirent\n");

        hsp->op->new_dirent(hsp->dfh, $3);
   }
   ;


blank_or_indented_lines
   : BLANKLINE
   {
        $$ = hsp->op->new((void *)"blank_or_indented_lines");
        hsp->op->add($$,$1);
   }

   | FLOATING_LINE
   {
        $$ = hsp->op->new((void *)"blank_or_indented_lines");
        hsp->op->add($$,$1);
   }

   | blank_or_indented_lines
     BLANKLINE
   {
        hsp->op->add($1,$2);
   }

   | blank_or_indented_lines
     FLOATING_LINE
   {
        hsp->op->add($1,$2);
   }
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
