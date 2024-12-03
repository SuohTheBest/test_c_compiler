#ifndef TRANSLATE_H
#define TRANSLATE_H
#include "semantic.h"

int translate_code(char *out_put_file, Node *tree_root);
char *translate_midCode(Node *tree_root);
char *translate_ExtDef(Node *tree_node);
char *translate_VarList(Node *tree_node);
char *translate_CompSt(Node *tree_node);
char *translate_DefList(Node *tree_node);
char *translate_DecList(Node *tree_node);
char *translate_StmtList(Node *tree_node);
// todo
char *translate_Stmt(Node *tree_node);
char *translate_Exp(Node *tree_node);
char *get_mem(char *varName);
#endif