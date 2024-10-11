%{
#include "yystype.h"
#include "syntax.tab.h"
extern int error_flag;
extern int has_a_error;
extern void add_error(int lineno);
%}
%option yylineno
INT                         0|[1-9][0-9]*
FLOAT                       [0-9]+\.[0-9]+
TYPE                        (int|float)
STRUCT                      struct
RETURN                      return
IF                          if
ELSE                        else
WHILE                       while
LCOM                        "//"
LBCOM                       "/*"
RBCOM                       "*/"
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
{INT}                       {
                                NODE_INIT(INT)
                                yylval->val.i_val = atoi(yytext);
                                return INT;
                            }
{FLOAT}                     {
                                NODE_INIT(FLOAT)
                                yylval->val.f_val = atof(yytext);
                                return FLOAT;
                            }
{SEMI}                      {
                                NODE_INIT(SEMI)
                                return SEMI;
                            }
{LCOM}                      {
                                char c = input();
                                while (c != '\n' && c != EOF)
                                {
                                    c = input();
                                }
                            }
{LBCOM}                     {
                                char c1 = input(), c2 = input();
                                int flag = 0;
                                while (c2 != EOF){
                                    if(c1=='*' && c2=='/') {
                                        flag = 1;
                                        break;
                                    }
                                    c1 = c2, c2 = input();
                                }
                                if(!flag)add_error(yylineno);
                            }
{RBCOM}                     {
                                add_error(yylineno);
                            }
{COMMA}                     {
                                NODE_INIT(COMMA)
                                return COMMA;
                            }
{ASSIGNOP}                  {
                                NODE_INIT(ASSIGNOP)
                                return ASSIGNOP;
                            }
{RELOP}                     {
                                NODE_INIT(RELOP)
                                return RELOP;
                            }
{PLUS}                      {
                                NODE_INIT(PLUS)
                                return PLUS;
                            }
{MINUS}                     {
                                NODE_INIT(MINUS)
                                return MINUS;
                            }
{STAR}                      {
                                NODE_INIT(STAR)
                                return STAR;
                            }
{DIV}                       {
                                NODE_INIT(DIV)
                                return DIV;
                            }
{AND}                       {
                                NODE_INIT(AND)
                                return AND;
                            }
{OR}                        {
                                NODE_INIT(OR)
                                return OR;
                            }
{DOT}                       {
                                NODE_INIT(DOT)
                                return DOT;
                            }
{NOT}                       {
                                NODE_INIT(NOT)
                                return NOT;
                            }
{TYPE}                      {
                                NODE_INIT(TYPE)
                                if(strcmp(yytext,"int")==0)
                                    yylval->val.i_val= 0;
                                else yylval->val.i_val = 1;
                                return TYPE;
                            }
{LP}                        {
                                NODE_INIT(LP)
                                return LP;
                            }
{RP}                        {
                                NODE_INIT(RP)
                                return RP;
                            }
{LB}                        {
                                NODE_INIT(LB)
                                return LB;
                            }
{RB}                        {
                                NODE_INIT(RB)
                                return RB;
                            }
{LC}                        {
                                NODE_INIT(LC)
                                return LC;
                            }
{RC}                        {
                                NODE_INIT(RC)
                                return RC;
                            }
{STRUCT}                    {
                                NODE_INIT(STRUCT)
                                return STRUCT;
                            }
{RETURN}                    {
                                NODE_INIT(RETURN)
                                return RETURN;
                            }
{IF}                        {
                                NODE_INIT(IF)
                                return IF;
                            }
{ELSE}                      {
                                NODE_INIT(ELSE)
                                return ELSE;
                            }
{WHILE}                     {
                                NODE_INIT(WHILE)
                                return WHILE;
                            }
{ID}                        {
                                NODE_INIT(ID)
                                strcpy(yylval->val.id, yytext);
                                return ID;
                            }
.                           {
                                printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext);
                                has_a_error = 1;
                                return 0;
                            }
%%