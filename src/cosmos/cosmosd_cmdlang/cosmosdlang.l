%option reentrant stack noyywrap
%option bison-bridge bison-locations


%{
#include <stdlib.h>
#include "cosmosdlang.tab.h"
%}



%x RAWNUM
%x URLSTR
%x READCM


EOL  \n
READARGS    .{24)
NUM64       .{8}


%%

geti  BEGIN(URLSTR); return GETICMD;
stat  BEGIN(RAWNUM); return STATCMD;
look  BEGIN(RAWNUM); return LOOKCMD;
fopn  BEGIN(RAWNUM); return LOOKCMD;
read  BEGIN(READCM); return READCMD;

<URLSTR>(file[:][/][/][/]|http[s]?[:][/][/])[^\n\t]        {
          yylval = yytext;
          BEGIN(INITIAL);
          return URL;
        }

.+      {
          yylval = yytext;
          return STR;
        }

[\n]      return EOL;

EOF       return END;

<RAWNUM>{NUM64}        {
          yylval = yytext;
          BEGIN(INITIAL);
          return NUM64;
        }

<READCM>{READARGS}        {
          yylval = yytext;
          BEGIN(INITIAL);
          return READARGS;
        }

.       // consume
[\n]    // consume

%%