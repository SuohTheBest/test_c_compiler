#ifndef COMPILER_YYSTYPE_H
#define COMPILER_YYSTYPE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE Node *

// clang-format off
enum type_t {
    _FLOAT, _INT, _TYPE, _STRUCT, _RETURN, _IF, _ELSE, _WHILE, _SEMI, _COMMA, _LC, _RC, _ID,
    _ASSIGNOP, _AND, _OR, _RELOP, _PLUS, _MINUS, _MUL, _DIV, _NOT, _LP, _RP, _LB, _RB, _DOT, _STAR,
    _Program, _ExtDefList, _ExtDef, _ExtDecList, _Specifier, _StructSpecifier, _OptTag, _Tag,
    _VarDec, _FunDec, _VarList, _ParamDec, _CompSt, _StmtList, _Stmt, _DefList, _Def, _DecList,
    _Dec, _Exp, _Args,
};
// clang-format on

typedef struct Node {
    union val_t {
        char id[64];
        int i_val;
        float f_val;
    } val;
    enum type_t type;
    int lineno;
    struct Node *child;
    struct Node *brother;
} Node;

#define NODE_INIT(TYPE)            \
    yylval = malloc(sizeof(Node)); \
    yylval->type = _##TYPE;        \
    yylval->lineno = yylineno;     \
    yylval->val.i_val = 0;         \
    yylval->child = NULL;          \
    yylval->brother = NULL;

#define arg(n) (*args[n])

#define BUILDTREE(TYPE, NO)                \
    Node *root = malloc(sizeof(Node)),     \
         *zipper = NULL;                   \
    root->type = _##TYPE;                  \
    for (int i = 1; i <= NO; i++) {        \
        if (arg(i) == NULL) continue;      \
        if (zipper == NULL) {              \
            root->child = zipper = arg(i); \
            root->lineno = arg(i)->lineno; \
            continue;                      \
        }                                  \
        zipper->brother = arg(i);          \
        zipper = zipper->brother;          \
    }                                      \
    arg(0) = root;

#endif // COMPILER_YYSTYPE_H