#ifndef COMPILER_SEMANTIC_H
#define COMPILER_SEMANTIC_H

#include "yystype.h"
#include "string.h"

typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;

struct Type_ {
    enum {
        BASIC, ARRAY, STRUCTURE, FUNCTION
    } kind;
    union {
        int basic;
        struct {
            Type elem;
            int size;
        } array;
        FieldList structure;
        FieldList function;
    } data;
};

struct FieldList_ {
    char *name;
    Type type;
    FieldList tail;
};

typedef struct sem_node {
    char *name;
    Type type;
    int is_func_def;
} sem_node;

unsigned hash_pjw(char *name);

int add_type(char *name, Type type, int is_func_def);

int add_name(char *name, Type type, int is_func_def);

void sem_read_tree(Node* root);

sem_node *read_type(char *name);

sem_node *read_name(char *name);

Node *find_node(Node *node, enum type_t type);

Type read_Specifier(Node *node);

void read_ExtDecList(Node *node, Type type);

void read_ExtDef(Node *node);

void read_DecList(Node *node, Type type, FieldList struct_field);

void read_DefList(Node *node, FieldList field);

void read_Def(Node *node, FieldList field);

void read_VarDec(Node *node, Type type, FieldList struct_field);

#endif //COMPILER_SEMANTIC_H