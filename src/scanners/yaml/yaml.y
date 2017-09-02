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
%token <ob> LINE INDENTED_LINE
%token BLANKLINE NEWLINE
%token END
%token OL_BODY_START
%token OL_BODY_END

%type <ob> dir_of_outline_blocks indented_line_recursive_area outline outline_block 

%token indented_line_recursive_area_t outline_t outline_block_t dir_of_outline_blocks_t


%destructor { free ($$); } <str>
%destructor { mapcel_cleanup($$); } <ob>

%{
    int num_ox = 0;
    int prev_indent = 0;
    void *ruleid;
%}

%%

ox_good			: ox
			  {
			      printf("\n");
			      printf("ox good.\n"); return;
			  }
			;


/* HIERARCHY LEVEL */

ox	: dir_of_outline_blocks
	  END
    {
       printf("ox\n");
    }

	| dir_of_outline_blocks
	  blank_or_indented_lines
	  END

	| blank_or_indented_lines
	  dir_of_outline_blocks
	  END

	| blank_or_indented_lines
	  dir_of_outline_blocks
	  blank_or_indented_lines
	  END

	;

dir_of_outline_blocks
	: outline_block
	{
       ruleid = (void *)"dir_of_outline_blocks";

		$$ = hsp->op->new(ruleid);

		hsp->op->add($$, $1);
       hsp->op->new_dirent(hsp->dfh, $1);

       hsp->op->new_dir(hsp->dfh, $$);
	}

	| dir_of_outline_blocks
	  blank_or_indented_lines
	  outline_block
	{
		hsp->op->add($$, $1);
       hsp->op->new_dirent(hsp->dfh, $3);
	}
   ;


outline_block	
	: outline
	{
       ruleid = (void *)"outline_block";
		$$ = hsp->op->new(ruleid);
		hsp->op->add($$,$1);
		hsp->op->new_dirent(hsp->dfh, $1);
	}

	| outline_block
	  outline
	{
		hsp->op->add($$,$2);
		hsp->op->new_dirent(hsp->dfh, $2);
	}
	;


outline
	: LINE
	{
       ruleid = (void *)"outline";
		$$ = hsp->op->new(ruleid);
       hsp->op->add($$, $1);
	}

	| LINE
     indented_line_recursive_area
   {
       ruleid = (void *)"outline";
		$$ = hsp->op->new(ruleid);
       hsp->op->add($$, $1);
       hsp->op->add($$, $2);
		hsp->op->new_dirent(hsp->dfh, $$);
	}
	;


indented_line_recursive_area
	: INDENT
	  INDENTED_LINE
	{
        ruleid = (void *)"indented_line_recursive_area";
        $$ = hsp->op->new(ruleid);
        hsp->op->add($$, $1);
        hsp->op->add($$, $2);
	}

	| indented_line_recursive_area
	  INDENT
	  INDENTED_LINE
	{
		hsp->op->add($$, $2);
		hsp->op->add($$, $3);
	}
	;



/* NON MAPPING */

blank_or_indented_lines
	: BLANKLINE

	| BLANKLINE
	  blank_or_indented_lines2
	;


blank_or_indented_lines2
	: BLANKLINE

	| INDENT
	  INDENTED_LINE

	| blank_or_indented_lines2
	  BLANKLINE

	| blank_or_indented_lines2
	  INDENT INDENTED_LINE
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
   - bison caveat
*/
yyerror(char const *s) {
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
