%{
#include <stdio.h>
%}

%%
\"([^\"\\]|\\.)*\"   { printf("TOKEN_STRING: %s\n", yytext); }
.|\n                { /* Ignorar caracteres não correspondentes a STRING */ }

%%

int main() {
    yylex();
    return 0;
}
