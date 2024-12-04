#include "syntax.h"

#ifdef DEBUG
#define YYDEBUG 1
#endif

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

void print_error() {
    if (has_a_error) {
        error_flag = 1;
        return;
    } else if (cnt_errorb > 0) {
        error_flag = 1;
        for (int i = 0; i < cnt_errorb; ++i) {
            printf("Error type B at Line %d: Syntax error.\n", error_lineno[i]);
        }
    }
}

int syntax_analysis(char *fileName) {
    memset(error_lineno, 0, sizeof(error_lineno));
    FILE *f = fopen(fileName, "r");
    if (f == NULL) assert(0);
    yyrestart(f);
    yyparse();
    fclose(f);
    print_error();
    // if (error_flag == 0) print_tree(tree_root, 0);
    return error_flag;
}