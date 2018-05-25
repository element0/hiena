
%code requires {

#include "../../lookup_svc.h"
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

%type <lookup_target_t *> fudge fudge_seg find_child modifier 


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
      look->step_segment(look);
    }
  ;

fudge_seg
  : %empty
  | find_child
    {
      look->set_target(look, $1);
    }
  | fudge_seg find_prop
    {
      look->set_target(look, $2);
    }
  | fudge_seg transform
    {
      look->set_target(look, $2);
    }
  ;

find_child :
    IDENTIFIER
  {
    $$ = look->find_child(look, $1);
  }
  ;

find_prop :
    COLON IDENTIFIER
  {
    $$ = look->find_prop(look, $2);
  }

transform :
    DOT IDENTIFIER
  {
    $$ = look->tansform(look, $2);
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

int fudge_parse( struct lookup_hdl *h )
{
    yyscan_t scanner;

    yylex_init_extra( h, &scanner );

    yyset_in( NULL, scanner );
    
    yyparse(scanner, h);

    yylex_destroy(scanner);

    return 0;
}