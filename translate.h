#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "semantic.h"

typedef struct ArgsList {
    char argName[64];
    struct ArgsList *next;
} ArgsList;

int translate_code(char *output_file, Node *tree_root);

char *translate_midCode(Node *tree_root);

char *translate_ExtDef(Node *tree_node);

char *translate_VarList(Node *tree_node);

char *translate_CompSt(Node *tree_node);

char *translate_DefList(Node *tree_node);

char *translate_DecList(Node *tree_node);

char *translate_StmtList(Node *tree_node);

char *translate_Stmt(Node *tree_node);

char *translate_Exp(Node *tree_node, char *place);

char *translate_Cond(Node *tree_node, char *label_true, char *label_false);

char *translate_funcCall(Node *tree_node, char *place);

char *translate_Args(Node *tree_node, ArgsList *argsList);

char *translate_CondExp(Node *tree_node, char *place);

char *translate_AssExp(Node *tree_node, char *place);

char *translate_CulExp(Node *tree_node, char *place);

char *get_arrLocation(Node *tree_node, char *place, Type *eleType);

char *get_mem(char *varName);

char *new_tmp();

char *new_label();

#endif