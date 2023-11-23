%{
   /* definições de constantes manifestas
   LT, LE, EQ, NE, GT, GE,
   IF, THE, ELSE, ID, WHILE
   NUMBER, RELOP
    */
%}

/* definições regulares */

delim   [ \r\n]
ws      {delim}+
letter  [A-Za-z]
letter_ {letter}+_*
digit   [0-9]
id      {letter_}({letter_}|{digit})*
number  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

string  \"([^\"\\]|\\.)*\"

%%
{ws}     {/* nenhuma ação */}
if       {return(IF);}
then     {return(THEN);}
else     {return(ELSE);}
while    {return(WHILE);}
{id}     {yylval = (int) installID(); return(ID);}
{number} {yylval = (int) installNum(); return(NUMBER);}
"<"      {yylval = LT; return(RELOP);}
"<="     {yylval = LE; return(RELOP);}
"=="     {yylval = EQ; return(RELOP);}
"!>"     {yylval = NE; return(RELOP);}
">"      {yylval = GT; return(RELOP);}
">="     {yylval = GE; return(RELOP);}
%%

int installID() {

}

int installNum() {

}