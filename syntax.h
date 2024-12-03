#ifndef SYNTAX_H
#define SYNTAX_H
#include "syntax.tab.h"
#include "yystype.h"

extern void yyrestart(FILE *inputfile);
extern Node *tree_root;
extern int error_flag, has_a_error, cnt_errorb, yydebug;
extern int error_lineno[512];
extern char type_map[49][16];
void print_tree(Node *root, int depth);
void print_error();
int syntax_analysis(char *fileName);
#endif