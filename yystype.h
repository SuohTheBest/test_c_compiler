#ifndef COMPILER_YYSTYPE_H
#define COMPILER_YYSTYPE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum type_t {
    _FLOAT,
    _INT,
    _TYPE,
    _STRUCT,
    _RETURN,
    _IF,
    _ELSE,
    _WHILE,
    _SEMI,
    _COMMA,
    _LC,
    _RC,
    _ID,
    _ASSIGNOP,
    _AND,
    _OR,
    _RELOP,
    _PLUS,
    _MINUS,
    _MUL,
    _DIV,
    _NOT,
    _LP,
    _RP,
    _LB,
    _RB,
    _DOT,
    _STAR,
    _Program,
    _ExtDefList,
    _ExtDef,
    _ExtDecList,
    _Specifier,
    _StructSpecifier,
    _OptTag,
    _Tag,
    _VarDec,
    _FunDec,
    _VarList,
    _ParamDec,
    _CompSt,
    _StmtList,
    _Stmt,
    _DefList,
    _Def,
    _DecList,
    _Dec,
    _Exp,
    _Args,
    _OTHER,
};

extern char type_map[49][16];

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

// #define DEBUG
#define YYSTYPE Node *
#ifdef DEBUG
#define lexprintf(p1, p2) printf(p1, p2)
#else
#define lexprintf(p1, p2)
#endif

#define NODE_INIT(TYPE)                \
    lexprintf(#TYPE " %s\n", yytext);  \
    Node *node = malloc(sizeof(Node)); \
    node->type = _##TYPE;              \
    node->lineno = yylineno;           \
    node->child = NULL;                \
    node->brother = NULL;

#define NODE_RETURN(TYPE) \
    yylval = node;        \
    return TYPE;

#define add_brother(NO)                                          \
    ptr = NULL;                                                  \
    for (int i = NO - 1; i > 0; i--) {                           \
        if ((*n[i])->type == _OTHER) continue;                   \
        ptr = *n[i];                                             \
        break;                                                   \
    }                                                            \
    if (ptr == NULL) assert(0 && "couldn't find non-null ptr!"); \
    while (ptr->brother != NULL) ptr = ptr->brother;             \
    ptr->brother = *n[NO];

#define add_father(TYPE)               \
    Node *node = malloc(sizeof(Node)); \
    node->type = _##TYPE;              \
    node->lineno = (*n[1])->lineno;    \
    node->child = *n[1];               \
    node->brother = NULL;              \
    *n[0] = node;

#define build1(TYPE) add_father(TYPE)

#define build2(TYPE) build1(TYPE) \
    add_brother(2)

#define build3(TYPE) build2(TYPE) \
    add_brother(3)

#define build4(TYPE) build3(TYPE) \
    add_brother(4)

#define build5(TYPE) build4(TYPE) \
    add_brother(5)

#define build6(TYPE) build5(TYPE) \
    add_brother(6)

#define build7(TYPE) build6(TYPE) \
    add_brother(7)
#endif // COMPILER_YYSTYPE_H