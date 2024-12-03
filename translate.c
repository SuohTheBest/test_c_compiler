#include "translate.h"
int error_flag;
char relOP[6][3] = {">", "<", ">=", "<=", "==", "!="};

Node *find_brother(Node *tree_node, enum type_t tar_type) {
    while (tree_node != NULL && tree_node->type != tar_type)
        tree_node = tree_node->brother;
    return tree_node;
}

char *strcatm(char *s1, char *mid, char *s2) {
    if (strlen(s1) == 0) return s2;
    if (strlen(s2) == 0) return s1;
    char *ret = calloc(strlen(s1) + strlen(s2) + strlen(mid) + 4, sizeof(char));
    sprintf(ret, "%s%s%s", s1, mid, s2);
    return ret;
}

int translate_code(char *out_put_file, Node *tree_root) {
    char *midCode = translate_midCode(tree_root->child);
    if (error_flag) {
        printf("Cannot translate: Code contains variables or parameters of structure type.");
        return error_flag;
    }
    FILE *f = fopen(out_put_file, "r");
    if (f == NULL) assert(0);
    fputs(midCode, f);
    fclose(f);
    return error_flag;
}

char *translate_midCode(Node *tree_root) {
    if (tree_root == NULL) return "";
    if (tree_root->type == _ExtDefList)
        return translate_midCode(tree_root->child);
    if (tree_root->type == _ExtDef) {
        char *s1 = translate_ExtDef(tree_root);
        char *s2 = translate_midCode(tree_root->brother);
        return strcatm(s1, "\n\n", s2);
    }
    return "";
}

char *translate_ExtDef(Node *tree_node) {
    tree_node = tree_node->child;
    Node *funDec = find_brother(tree_node, _FunDec);
    if (funDec == NULL) return "";
    funDec = funDec->child;
    Node *funId = find_brother(funDec, _ID);
    char *funName = strcatm(funId->val.id, "", "");
    Node *varList = find_brother(funDec, _VarList);
    char *args = varList == NULL ? "" : translate_VarList(varList);
    Node *compSt = find_brother(funDec, _CompSt);
    char *codeBlock = translate_CompSt(compSt);
    char *ret = strcatm("FUNCTION ", funName, " :");
    ret = strcatm(ret, "\n", args);
    ret = strcatm(ret, "\n", codeBlock);
    return ret;
}

char *translate_VarList(Node *tree_node) {
    tree_node = tree_node->child;
    Node *paramDec = tree_node->child;
    paramDec = find_brother(paramDec, _VarDec);
    while (paramDec->type != _ID) paramDec = paramDec->child;
    char *ret = strcatm("PARAM ", "", paramDec->val.id);
    Node *nbrVarList = find_brother(tree_node, _VarList);
    if (nbrVarList != NULL) {
        char *s1 = translate_VarList(nbrVarList);
        ret = strcatm(ret, "\n", s1);
    }
    return ret;
}

char *translate_CompSt(Node *tree_node) {
    tree_node = tree_node->child;
    Node *defList = find_brother(tree_node, _DefList);
    char *s1 = defList == NULL ? "" : translate_DefList(defList);
    Node *stmtList = find_brother(tree_node, _StmtList);
    char *s2 = stmtList == NULL ? "" : translate_StmtList(stmtList);
    return strcatm(s1, "\n", s2);
}

char *translate_DefList(Node *tree_node) {
    if (tree_node == NULL) return "";
    if (tree_node->type == _DefList) return translate_DefList(tree_node->child);
    if (tree_node->type == _Def) {
        char *s1 = translate_DecList(find_brother(tree_node->child, _DecList));
        char *s2 = translate_DefList(tree_node->brother);
        return strcatm(s1, "\n", s2);
    }
    return "";
}

char *translate_DecList(Node *tree_node) {
    Node *dec = tree_node->child->child;
    char *s1;
    if (find_brother(dec, _ASSIGNOP) == NULL)
        s1 = "";
    else {
        Node *varDec = find_brother(dec, _VarDec);
        while (varDec->type != _ID) varDec = varDec->child;
        char *varName = varDec->val.id;
        char *sm = get_mem(varName);
        char *exp = translate_Exp(find_brother(dec, _Exp));
        exp = strcatm(varName, "=", exp);
        s1 = strcatm(sm, "\n", exp);
    }
    Node *nbrDecList = find_brother(tree_node->child, _DecList);
    char *s2 = translate_DecList(nbrDecList);
    return strcatm(s1, "\n", s2);
}

char *translate_StmtList(Node *tree_node) {
    if (tree_node == NULL) return "";
    if (tree_node->type == _StmtList) return translate_StmtList(tree_node->child);
    if (tree_node->type == _Stmt) {
        char *s1 = translate_Stmt(tree_node);
        char *s2 = translate_StmtList(tree_node->brother);
        return strcatm(s1, "\n", s2);
    }
    return "";
}