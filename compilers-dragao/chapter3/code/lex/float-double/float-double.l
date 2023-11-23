%{
#include <stdio.h>
%}

%%
float {printf("double");}
.|\n  {printf("%s", yytext);}
%%

int main() {
    yylex();
    return 0;
}