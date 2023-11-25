%{
   void print_word(char *w);
%}

letter      [A-Za-z]
word        {letter}+
vowel       a|e|i|o|u
vowel_start {vowel}{word}
ws          [ \t\r]

%%
{vowel_start} {printf("%say", yytext);}
{word}        {print_word(yytext);}
{ws}          {printf("%s", yytext);}
%%

#include <stdio.h>

void print_word(char *w)
{
   char first = *w;
   w++;
   printf("%s%cay", w, first);
}

int main()
{
   yylex();
   return 0;
}