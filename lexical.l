%{
#include "yystype.h"
#include "syntax.tab.h"
extern int is_ok;
%}
INT                         0|[1-9][0-9]*
FLOAT                       [0-9]+\.[0-9]+
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
LCOM                        "//"
LBCOM                       "/*"
RBCOM                       "*/"
%%
[ \r\t\n]                   {}
{INT}                       {
                                NODE_INIT(INT)
                                node->val.i_val = atoi(yytext);
                                NODE_RETURN(INT)
                            }
{FLOAT}                     {
                                NODE_INIT(FLOAT)
                                node->val.f_val = atof(yytext);
                                NODE_RETURN(FLOAT)
                            }
{SEMI}                      {
                                NODE_INIT(SEMI)
                                NODE_RETURN(SEMI)
                            }
{COMMA}                     {
                                NODE_INIT(COMMA)
                                NODE_RETURN(COMMA)
                            }
{ASSIGNOP}                  {
                                NODE_INIT(ASSIGNOP)
                                NODE_RETURN(ASSIGNOP)
                            }
{RELOP}                     {
                                NODE_INIT(RELOP)
                                NODE_RETURN(RELOP)
                            }
{PLUS}                      {
                                NODE_INIT(PLUS)
                                NODE_RETURN(PLUS)
                            }
{MINUS}                     {
                                NODE_INIT(MINUS)
                                NODE_RETURN(MINUS)
                            }
{STAR}                      {
                                NODE_INIT(STAR)
                                NODE_RETURN(STAR)
                            }
{DIV}                       {
                                NODE_INIT(DIV)
                                NODE_RETURN(DIV)
                            }
{AND}                       {
                                NODE_INIT(AND)
                                NODE_RETURN(AND)
                            }
{OR}                        {
                                NODE_INIT(OR)
                                NODE_RETURN(OR)
                            }
{DOT}                       {
                                NODE_INIT(DOT)
                                NODE_RETURN(DOT)
                            }
{NOT}                       {
                                NODE_INIT(NOT)
                                NODE_RETURN(NOT)
                            }
{TYPE}                      {
                                NODE_INIT(TYPE)
                                if(strcmp(yytext,"int")==0)
                                    node->val.i_val= 0;
                                else node->val.i_val = 1;
                                NODE_RETURN(TYPE)
                            }
{LP}                        {
                                NODE_INIT(LP)
                                NODE_RETURN(LP)
                            }
{RP}                        {
                                NODE_INIT(RP)
                                NODE_RETURN(RP)
                            }
{LB}                        {
                                NODE_INIT(LB)
                                NODE_RETURN(LB)
                            }
{RB}                        {
                                NODE_INIT(RB)
                                NODE_RETURN(RB)
                            }
{LC}                        {
                                NODE_INIT(LC)
                                NODE_RETURN(LC)
                            }
{RC}                        {
                                NODE_INIT(RC)
                                NODE_RETURN(RC)
                            }
{STRUCT}                    {
                                NODE_INIT(STRUCT)
                                NODE_RETURN(STRUCT)
                            }
{RETURN}                    {
                                NODE_INIT(RETURN)
                                NODE_RETURN(RETURN)
                            }
{IF}                        {
                                NODE_INIT(IF)
                                NODE_RETURN(IF)
                            }
{ELSE}                      {
                                NODE_INIT(ELSE)
                                NODE_RETURN(ELSE)
                            }
{WHILE}                     {
                                NODE_INIT(WHILE)
                                NODE_RETURN(WHILE)
                            }
{ID}                        {
                                NODE_INIT(ID)
                                strcpy(yytext, node->val.id);
                                NODE_RETURN(ID);
                            }
{LCOM}                      {
                                char c = input();
                                while (c != '\n' && c != EOF) c = input();
                                return OTHER;
                            }
{LBCOM}                     {
                                char c1 = input(), c2 = input();
                                while (c2 != '\n' && c2 != EOF){
                                    if(c1=='*' && c2=='/') return OTHER;
                                    c1 = c2;
                                    c2 = input();
                                }
                                is_ok = 0;
                                printf("Error type B at Line %d: Missing '*/'\n", yylineno);
                                return OTHER;
                            }
{RBCOM}                     {
                                is_ok = 0;
                                printf("Error type B at Line %d: Syntax Error.\n", yylineno);
                                return OTHER;
                            }
.                           {
                                printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext);
                                is_ok = 0;
                                return OTHER;
                            }
%%