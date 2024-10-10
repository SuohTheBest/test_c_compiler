#include "syntax.tab.h"
#include "yystype.h"
#include <stdio.h>

extern void yyrestart(FILE *inputfile);

extern Node *tree_root;
extern int is_ok;
extern Node *null_node;

char type_map[49][16] = {"FLOAT", "INT", "TYPE", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "SEMI",
                         "COMMA", "LC", "RC", "ID", "ASSIGNOP", "AND", "OR", "RELOP", "PLUS",
                         "MINUS", "MUL", "DIV", "NOT", "LP", "RP", "LB", "RB", "DOT", "STAR",
                         "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
                         "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
                         "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
                         "Dec", "Exp", "Args"};

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
    yyrestart(f);
    yyparse();
    if (is_ok) print_tree(tree_root, 0);
    return 0;
}