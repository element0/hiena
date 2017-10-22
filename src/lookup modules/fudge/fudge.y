
%code requires {

#include "../../lookup_hdl.h"
#include "../../dcel.h"

typedef void* yyscan_t;
}

%define lr.type ielr
%define api.pure //full
%locations
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%parse-param {struct lookup_hdl *h}


%token <str> IDENTIFIER
%token FWD_SLASH
%token COLON
%token END

%type <struct hiena_dcel *> prod_instr find_child find_prop find_scan fudge_seg fudge


%%

fudge_good :
    fudge END;
  {
    h->result = h->target;

    return 0;
  }
  ;

fudge :
    fudge_seg
  | fudge fudge_seg
  ;

fudge_seg :
    prod_instr
  {
    h->set_target( p, $1 );
  }
  ;

prod_instr :
    find_child
  | find_prop
  | grind_scan
  ;

find_child :
    IDENTIFIER
  {
    $$ = h->find_child( h, $1 );
  }
  | FWD_SLASH IDENTIFIER
  {
    $$ = h->find_child( h, $2 );
  }
  ;

find_prop :
    COLON IDENTIFIER
  {
    $$ = h->find_prop( h, $2 );
  }
  ;

grind_scan :
    DOT IDENTIFIER
  {
    $$ = h->grind( h, $2 );
  }
  ;

%%

/* leave return type blank
 *  - bison caveat
 */
yyerror(char const *s)
{
    fprintf(stderr, "fudge err: %s\n", s);
}

struct hiena_dcel *fudge_parse(struct lookup_hdl *h)
{
    yyscan_t scanner;
    yylex_init_extra( h, &scanner );

    yyset_in( NULL, scanner );
    
    yyparse(scanner, h);

    yylex_destroy(scanner);

    return 0;
}