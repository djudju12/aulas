%{
#include <stdio.h>
%}

dspace " "+

%%
{dspace} {printf(" ");}
.|\n     {printf("%s", yytext);}
%%

int main() {
    yylex();
    return 0;
}