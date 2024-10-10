%{
#include "lex.yy.c"
#include "yystype.h"

void yyerror(char *msg);
Node *tree_root = NULL;
int is_ok = 1;
Node **n[8];
Node *ptr;
Node *null_node;
%}

/* declared tokens */
%token FLOAT INT TYPE STRUCT RETURN IF ELSE WHILE SEMI COMMA LC RC ID
%token ASSIGNOP AND OR RELOP PLUS MINUS DIV NOT STAR LP RP LB RB DOT
%token OTHER
%right ASSIGNOP
%left AND OR
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT
%%
Program :                   ExtDefList                      {n[0] = &$$;n[1] = &$1;build1(Program);tree_root=$$;}
;
ExtDefList :                ExtDef ExtDefList               {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(ExtDefList)}
                            |                               {$$ = null_node;}
;
ExtDef :                    Specifier ExtDecList SEMI       {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(ExtDef)}
                            | Specifier SEMI                {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(ExtDef)}
                            | Specifier FunDec CompSt       {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(ExtDef)}
;
ExtDecList :                VarDec                          {n[0] = &$$;n[1] = &$1;build1(ExtDecList)}
                            | VarDec COMMA ExtDecList       {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(ExtDecList)}
;
Specifier :                 TYPE                            {n[0] = &$$;n[1] = &$1;build1(Specifier)}
                            | StructSpecifier               {n[0] = &$$;n[1] = &$1;build1(Specifier)}
;
StructSpecifier :           STRUCT OptTag LC DefList RC     {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;n[5] = &$5;build5(StructSpecifier)}
                            | STRUCT Tag                    {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(StructSpecifier)}
;
OptTag :                    ID                              {n[0] = &$$;n[1] = &$1;build1(OptTag)}
                            |                               {$$ = null_node;}
;
Tag :                       ID                              {n[0] = &$$;n[1] = &$1;build1(Tag)}
;
VarDec :                    ID                              {n[0] = &$$;n[1] = &$1;build1(VarDec)}
                            | VarDec LB INT RB              {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;build4(VarDec)}
;
FunDec :                    ID LP VarList RP                {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;build4(FunDec)}
                            | ID LP RP                      {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(FunDec)}
;
VarList :                   ParamDec COMMA VarList          {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(VarList)}
                            | ParamDec                      {n[0] = &$$;n[1] = &$1;build1(VarList)}
;
ParamDec :                  Specifier VarDec                {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(ParamDec)}
;
CompSt :                    LC DefList StmtList RC          {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;build4(CompSt)}
;
StmtList :                  Stmt StmtList                   {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(StmtList)}
                            |                               {$$ = null_node;}
;
Stmt :                      Exp SEMI                        {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(Stmt)}
                            | CompSt                        {n[0] = &$$;n[1] = &$1;build1(Stmt)}
                            | RETURN Exp SEMI               {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Stmt)}
                            | IF LP Exp RP Stmt             {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;n[5] = &$5;build5(Stmt)}
                            | IF LP Exp RP Stmt ELSE Stmt   {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;n[5] = &$5;n[6] = &$6;n[7] = &$7;build7(Stmt)}
                            | WHILE LP Exp RP Stmt          {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;n[5] = &$5;build5(Stmt)}
;
DefList :                   Def DefList                     {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(DefList)}
                            |                               {$$ = null_node;}
;
Def :                       Specifier DecList SEMI          {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Def)}
;
DecList :                   Dec                             {n[0] = &$$;n[1] = &$1;build1(DecList)}
                            | Dec COMMA DecList             {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(DecList)}
;
Dec :                       VarDec                          {n[0] = &$$;n[1] = &$1;build1(Dec)}
                            | VarDec ASSIGNOP Exp           {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Dec)}
;
Exp :                       Exp ASSIGNOP Exp                {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp AND Exp                   {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp OR Exp                    {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp RELOP Exp                 {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp PLUS Exp                  {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp MINUS Exp                 {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp STAR Exp                  {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp DIV Exp                   {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | LP Exp RP                     {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | MINUS Exp                     {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(Exp)}
                            | NOT Exp                       {n[0] = &$$;n[1] = &$1;n[2] = &$2;build2(Exp)}
                            | ID LP Args RP                 {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;build4(Exp)}
                            | ID LP RP                      {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | Exp LB Exp RB                 {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;n[4] = &$4;build4(Exp)}
                            | Exp DOT ID                    {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Exp)}
                            | ID                            {n[0] = &$$;n[1] = &$1;build1(Exp)}
                            | INT                           {n[0] = &$$;n[1] = &$1;build1(Exp)}
                            | FLOAT                         {n[0] = &$$;n[1] = &$1;build1(Exp)}
;
Args :                      Exp COMMA Args                  {n[0] = &$$;n[1] = &$1;n[2] = &$2;n[3] = &$3;build3(Args)}
                            | Exp                           {n[0] = &$$;n[1] = &$1;build1(Args)}
;
%%
void yyerror(char *msg) {
    fprintf(stderr, "error: %s\n", msg);
}