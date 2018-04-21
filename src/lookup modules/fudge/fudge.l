%option reentrant stack noyywrap
%option bison-bridge bison-locations
%option extra-type="struct lookup_hdl *"


%{
#include "../../lookup_hdl.h"
#include "fudge.tab.h"
%}

%%

[.]     return DOT;
[/]+    return FWD_SLASH;
[:]     return COLON;
.+      {
          yylval = yytext;
          return IDENTIFIER;
        }

[\n]    return END;
EOF     return END;
.       // consume

%%
