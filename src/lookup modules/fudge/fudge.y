
%code requires {

#include "../../lookup_hdl.h"
#include "../../dcel.h"
#include "fudge.h"

typedef void* yyscan_t;
}

%define lr.type ielr
%define api.pure //full
%locations
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%parse-param {struct lookup_hdl *look}


%token <str> IDENTIFIER
%token FWD_SLASH
%token DOT
%token COLON
%token END

%type <struct hiena_dcel *> prod_instr find_child find_prop find_scan fudge_seg fudge


%%

%code {
        char *cmd;
}

fudge_good
  : fudge END
    {
      look->result = look->target;

      return 0;
    }
  ;

fudge
  : fudge_seg
  | fudge path_sep fudge_seg
  ;

path_sep
  : FWD_SLASH
    {
      look->step_aframe(look);
    }
  ;

fudge_seg
  : %empty
  | find_child
    {
      look->set_target(look, $1);
    }
  | fudge_seg modifier
    {
      look->set_target(look, $3);
    }
  ;

find_child :
    IDENTIFIER
  {
    $$ = look->find_child(look, $1);
  }
  ;

modifier :
    COLON IDENTIFIER
  {
    $$ = look->find_prop(look, $2);
  }
  | DOT IDENTIFIER
  {
    cmd = fudge_expand(look, $2);
    $$ = look->grind(look, cmd);
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