%{
#include "lex.yy.c"
#include "yystype.h"

void yyerror(char *msg);
void add_error(int lineno);
int error_flag = 0;
Node *tree_root=NULL;
int error_lineno[1024], cnt_errorb = 0;
int has_a_error = 0;
%}

/* declared tokens */
%token FLOAT INT TYPE STRUCT RETURN IF ELSE WHILE SEMI COMMA LC RC ID
%token ASSIGNOP AND OR RELOP PLUS MINUS DIV NOT STAR LP RP LB RB DOT
%right ASSIGNOP
%left AND OR
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
Program :                   ExtDefList                      {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Program, 1);
                                                                tree_root=$$;
                                                            }
;
ExtDefList :                ExtDef ExtDefList               {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(ExtDefList, 2);
                                                            }
                            |                               {   $$ = NULL; }
;
ExtDef :                    Specifier ExtDecList SEMI       {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(ExtDef, 3);
                                                            }
                            | Specifier SEMI                {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(ExtDef, 2);
                                                            }
                            | Specifier FunDec CompSt       {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(ExtDef, 3);
                                                            }
                            | Specifier error SEMI          {   yyerrok; }
;
ExtDecList :                VarDec                          {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(ExtDecList, 1);
                                                            }
                            | VarDec COMMA ExtDecList       {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(ExtDecList, 3);
                                                            }
;
Specifier :                 TYPE                            {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Specifier, 1);
                                                            }
                            | StructSpecifier               {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Specifier, 1);
                                                            }
;
StructSpecifier :           STRUCT OptTag LC DefList RC     {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4, &$5};
                                                                BUILDTREE(StructSpecifier, 5);
                                                            }
                            | STRUCT Tag                    {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(StructSpecifier, 2);
                                                            }
;
OptTag :                    ID                              {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(OptTag, 1);
                                                            }
                            |                               {   $$ = NULL; }
;
Tag :                       ID                              {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Tag, 1);
                                                            }
;
VarDec :                    ID                              {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(VarDec, 1);
                                                            }
                            | VarDec LB INT RB              {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4};
                                                                BUILDTREE(VarDec, 4);
                                                            }
;
FunDec :                    ID LP VarList RP                {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4};
                                                                BUILDTREE(FunDec, 4);
                                                            }
                            | ID LP RP                      {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(FunDec, 3);
                                                            }
                            | error RP                      {   yyerrok; }
;
VarList :                   ParamDec COMMA VarList          {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(VarList, 3);
                                                            }
                            | ParamDec                      {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(VarList, 1);
                                                            }
;
ParamDec :                  Specifier VarDec                {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(ParamDec, 2);
                                                            }
;
CompSt :                    LC DefList StmtList RC          {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4};
                                                                BUILDTREE(CompSt, 4);
                                                            }
                            | error RC                      {   yyerrok; }
;
StmtList :                  Stmt StmtList                   {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(StmtList, 2);
                                                            }
                            |                               {   $$ = NULL; }
;
Stmt :                      Exp SEMI                        {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(Stmt, 2);
                                                            }
                            | CompSt                        {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Stmt, 1);
                                                            }
                            | RETURN Exp SEMI               {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Stmt, 3);
                                                            }
                            | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
                                                            {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4, &$5};
                                                                BUILDTREE(Stmt, 5);
                                                            }
                            | IF LP Exp RP Stmt ELSE Stmt   {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4, &$5, &$6, &$7};
                                                                BUILDTREE(Stmt, 7);
                                                            }
                            | WHILE LP Exp RP Stmt          {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4, &$5};
                                                                BUILDTREE(Stmt, 5);
                                                            }
                            | error SEMI                    {   yyerrok; }
                            | WHILE error RP Stmt           {   yyerrok; }
                            | IF error RP Stmt %prec LOWER_THAN_ELSE
                                                            {   yyerrok; }
                            | IF error RP Stmt ELSE Stmt    {   yyerrok; }
;
DefList :                   Def DefList                     {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(DefList, 2);
                                                            }
                            |                               {   $$ = NULL; }
;
Def :                       Specifier DecList SEMI          {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Def, 3);
                                                            }
                            | Specifier error SEMI          {   yyerrok; }
;
DecList :                   Dec                             {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(DecList, 1);
                                                            }
                            | Dec COMMA DecList             {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(DecList, 3);
                                                            }
;
Dec :                       VarDec                          {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Dec, 1);
                                                            }
                            | VarDec ASSIGNOP Exp           {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Dec, 3);
                                                            }
;
Exp :                       Exp ASSIGNOP Exp                {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp AND Exp                   {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp OR Exp                    {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp RELOP Exp                 {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp PLUS Exp                  {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp MINUS Exp                 {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp STAR Exp                  {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp DIV Exp                   {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | LP Exp RP                     {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | MINUS Exp                     {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(Exp, 2);
                                                            }
                            | NOT Exp                       {
                                                                Node **args[8] = {&$$, &$1, &$2};
                                                                BUILDTREE(Exp, 2);
                                                            }
                            | ID LP Args RP                 {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4};
                                                                BUILDTREE(Exp, 4);
                                                            }
                            | ID LP RP                      {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | Exp LB Exp RB                 {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3, &$4};
                                                                BUILDTREE(Exp, 4);
                                                            }
                            | Exp DOT ID                    {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Exp, 3);
                                                            }
                            | ID                            {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Exp, 1);
                                                            }
                            | INT                           {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Exp, 1);
                                                            }
                            | FLOAT                         {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Exp, 1);
                                                            }
;
Args :                      Exp COMMA Args                  {
                                                                Node **args[8] = {&$$, &$1, &$2, &$3};
                                                                BUILDTREE(Args, 3);
                                                            }
                            | Exp                           {
                                                                Node **args[8] = {&$$, &$1};
                                                                BUILDTREE(Args, 1);
                                                            }
;
%%
void yyerror(char *msg) {
    add_error(yylineno);
}
void add_error(int lineno) {
    if (cnt_errorb == 0 || error_lineno[cnt_errorb - 1] != lineno)
        error_lineno[cnt_errorb++] = lineno;
}