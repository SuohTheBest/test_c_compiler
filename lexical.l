%{
#include <stdio.h>
//#define DEBUG
#ifdef DEBUG
#define lexprintf(p1,p2) printf(p1,p2)
#else
#define lexprintf(p1,p2)
#endif
%}
INT_DEC                     [1-9][0-9]*
INT_OCT                     0[0-7]*
INT_HEX                     0[xX][0-9A-Fa-f]+
FLOAT                       [0-9]+\.[0-9]+
FLOAT_SCI                   ([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)[eE][-+]?[0-9]+
TYPE                        (int|float)
STRUCT                      struct
RETURN                      return
IF                          if
ELSE                        else
WHILE                       while
SEMI                        ";"
COMMA                       ","
ASSIGNOP                    "="
RELOP                       >|<|>=|<=|==|!=
PLUS                        "+"
MINUS                       "-"
STAR                        "*"
DIV                         "/"
AND                         "&&"
OR                          "||"
DOT                         \.
NOT                         "!"
LP                          \(
RP                          \)
LB                          \[
RB                          \]
LC                          \{
RC                          \}
ID                          [a-zA-Z_][a-zA-Z0-9_]*
%%
[ \r\t\n]                   {}
{INT_DEC}                   {lexprintf("INT_DEC %d\n",atoi(yytext));}
{INT_OCT}                   {lexprintf("INT_OCT %d\n",atoi(yytext));}
{INT_HEX}                   {lexprintf("INT_HEX %d\n",atoi(yytext));}
{FLOAT}                     {lexprintf("FLOAT %f\n",atof(yytext));}
{FLOAT_SCI}                 {lexprintf("FLOAT_SCI %f\n",atof(yytext));}
{SEMI}                      {lexprintf("SEMI %s\n",yytext);}
{COMMA}                     {lexprintf("COMMA %s\n",yytext);}
{ASSIGNOP}                  {lexprintf("ASSIGNOP %s\n",yytext);}
{RELOP}                     {lexprintf("RELOP %s\n",yytext);}
{PLUS}                      {lexprintf("PLUS %s\n",yytext);}
{MINUS}                     {lexprintf("MINUS %s\n",yytext);}
{STAR}                      {lexprintf("STAR %s\n",yytext);}
{DIV}                       {lexprintf("DIV %s\n",yytext);}
{AND}                       {lexprintf("AND %s\n",yytext);}
{OR}                        {lexprintf("OR %s\n",yytext);}
{DOT}                       {lexprintf("DOT %s\n",yytext);}
{NOT}                       {lexprintf("NOT %s\n",yytext);}
{TYPE}                      {lexprintf("TYPE %s\n",yytext);}
{LP}                        {lexprintf("LP %s\n",yytext);}
{RP}                        {lexprintf("RP %s\n",yytext);}
{LB}                        {lexprintf("LB %s\n",yytext);}
{RB}                        {lexprintf("RB %s\n",yytext);}
{LC}                        {lexprintf("LC %s\n",yytext);}
{RC}                        {lexprintf("RC %s\n",yytext);}
{STRUCT}                    {lexprintf("STRUCT %s\n",yytext);}
{RETURN}                    {lexprintf("RETURN %s\n",yytext);}
{IF}                        {lexprintf("IF %s\n",yytext);}
{ELSE}                      {lexprintf("ELSE %s\n",yytext);}
{WHILE}                     {lexprintf("WHILE %s\n",yytext);}
{ID}                        {lexprintf("ID %s\n",yytext);}
.                           {printf("Error type A at Line %d: Mysterious characters \'%s\'\n",yylineno, yytext);}
%%
int main(int argc, char** argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return 1;
        }
    }
    while(yylex() != 0);
    return 0;
}

