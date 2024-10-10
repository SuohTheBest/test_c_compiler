#include "syntax.tab.h"
#include "yystype.h"
#include <stdio.h>

extern void yyrestart(FILE *inputfile);

extern Node *tree_root;
extern int is_ok;
extern Node *null_node;

char type_map[49][16] = {"FLOAT", "INT", "TYPE", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "SEMI", "COMMA", "LC", "RC",
                         "ID",
                         "ASSIGNOP", "AND", "OR", "RELOP", "PLUS", "MINUS", "MUL", "DIV", "NOT", "LP", "RP", "LB", "RB",
                         "DOT",
                         "STAR", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
                         "OptTag", "Tag",
                         "VarDec", "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def",
                         "DecList", "Dec", "Exp",
                         "Args"};

void print_tree(Node *root, int depth) {
    if (root == NULL) return;
    enum type_t type = root->type;
    if (type == _OTHER) {
        print_tree(root->brother, depth);
        return;
    }
    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("%s", type_map[type]);
    if (type >= _Program)
        printf(" (%d)", root->lineno);
    else if (type == _ID)
        printf(": %s", root->val.id);
    else if (type == _TYPE) {
        if (root->val.i_val == 0)
            printf(": int");
        else
            printf(": float");
    } else if (type == _INT) {
        printf(": %d", root->val.i_val);
    } else if (type == _FLOAT) {
        printf(": %f", root->val.f_val);
    }
    printf("\n");
    fflush(stdout);
    print_tree(root->child, depth + 1);
    print_tree(root->brother, depth);
}

int main(int argc, char **argv) {
    null_node = malloc(sizeof(Node));
    null_node->type = _OTHER;
    if (argc <= 1) return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return 1;
    }

//    Node *t0, *t1, *t2, *t3, *ptr;
//    Node **n0 = &t0, **n1 = &t1, **n2 = &t2, **n3 = &t3;
//    Node *tmp = malloc(sizeof(Node));
//    tmp->child=NULL;
//    tmp->brother=NULL;
//    *n1 = tmp;
//    *n2 = tmp;
//    *n3 = tmp;
//    tmp->type = _DOT;
//    printf("Program" " \n");
//    Node *node = malloc(sizeof(Node));
//    node->type = _Program;
//    node->lineno = (*n1)->lineno;
//    node->child = *n1;
//    node->brother = ((void *) 0);
//    *n0 = node;
//    ptr = *n1;
//    while (ptr->brother != ((void *) 0)) ptr = ptr->brother;
//    ptr->brother = *n2;
//    ptr = *n2;
//    while (ptr->brother != ((void *) 0)) ptr = ptr->brother;
//    ptr->brother = *n3;
//    print_tree(*n0, 0);
    yyrestart(f);
    yyparse();
//    while (yylex() != 0);
    if (is_ok) print_tree(tree_root, 0);
    return 0;
}