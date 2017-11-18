
%code requires {
typedef void* yyscan_t;
}

%define lr.type ielr
%define api.pure //full
%locations
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}

%token <str> URL STR
%token NUM64
%token EOL END


%%

cosmosdlang_good :
    cosmosdlang END;
  {
    return 0;
  }
  ;

cosmoslang
  : cmd
  | cosmoslang cmd
  ;

cmd
  : getino
  | stat
  | lookup
  | fopen
  | read
  ;

/*---- cmds ----*/

getino
  : GETICMD URL EOL
  ;

stat
  : STATCMD ino EOL
  ;

lookup
  : LOOKCMD ino STR EOL
  ;

fopen
  : FOPNCMD ino EOL
  ;

read
  : READCMD READARGS EOL
  ;

ino
  : NUM64
  ;


%%

/* leave return type blank
 *  - bison caveat
 */
yyerror(char const *s)
{
    fprintf(stderr, "cosmosdlang err: %s\n", s);
}

 *cosmosdlang_parse()
{
    yyscan_t scanner;
    yylex_init_extra( &scanner );

    yyset_in( NULL, scanner );
    
    yyparse(scanner);

    yylex_destroy(scanner);

    return 0;
}