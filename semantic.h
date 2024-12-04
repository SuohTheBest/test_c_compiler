#ifndef COMPILER_SEMANTIC_H
#define COMPILER_SEMANTIC_H

#include "string.h"
#include "yystype.h"

typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;

struct Type_ {
    enum {
        BASIC,
        ARRAY,
        STRUCTURE,
        FUNCTION
    } kind;
    union {
        int basic;
        struct {
            Type elem;
            int size;
        } array;
        FieldList field;
    } data;
};

typedef struct Exp_Type {
    Type type;
    int l_val;
    int error;
} Exp_Type;

struct FieldList_ {
    char *name;
    Type type;
    FieldList tail;
};

typedef struct sem_node {
    char *name;
    Type type;
    int func_dec_lineno;
} sem_node;

unsigned hash_pjw(char *name);

int typeEqual(Type t1, Type t2);

void printType(Type t);

int add_sem_node(char *name, Type type, int func_dec_lineno);

void sem_read_tree(Node *root, FieldList f);

int semantic_analysis(Node *root);

sem_node *read_sem_node(char *name);

Type check_func_call(Node *node, FieldList f);

Node *find_node(Node *node, enum type_t type);

void read_VarList(Node *node, Type t);

void read_ParamDec(Node *node, Type t);

void read_CompSt(Node *node, Type t);

Type read_Specifier(Node *node);

Type read_FunDec(Node *node);

void read_ExtDecList(Node *node, Type t);

void read_ExtDef(Node *node);

Exp_Type read_Exp(Node *node);

void read_DecList(Node *node, Type curr_t, Type t);

void read_DefList(Node *node, Type t);

void read_Def(Node *node, Type t);

void read_VarDec(Node *node, Type curr_t, Type t);

#endif // COMPILER_SEMANTIC_H