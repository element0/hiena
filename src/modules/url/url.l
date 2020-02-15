%{
#include "skeleton.tab.h"
%}
%option reentrant stack bison-bridge bison-locations noyywrap
%option extra-type="Hsp *"

%%
[^:]
.				// consume
<<EOF>>		return END;

