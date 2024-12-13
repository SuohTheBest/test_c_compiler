#include "translate.h"

int ts_error_flag, tmpNo, labelNo;
char relOP[6][3] = {">", "<", ">=", "<=", "==", "!="};
char *midCode;

Node *find_brother(Node *tree_node, enum type_t tar_type) {
    while (tree_node != NULL && tree_node->type != tar_type)
        tree_node = tree_node->brother;
    return tree_node;
}

char *strcatm(char *s1, char *mid, char *s2) {
    if (s1 == NULL || strlen(s1) == 0) return s2;
    if (s2 == NULL || strlen(s2) == 0) return s1;
    char *ret = malloc(strlen(s1) + strlen(s2) + strlen(mid) + 4);
    sprintf(ret, "%s%s%s", s1, mid, s2);
    return ret;
}

int size_of_arr(Type t) {
    if (t->kind == BASIC) return 4;
    if (t->kind == ARRAY) {
        return t->data.array.size * size_of_arr(t->data.array.elem);
    }
    return -1;
}

int translate_code(char *output_file, Node *tree_root, int with_ir_output) {
    midCode = translate_midCode(tree_root->child);
    if (ts_error_flag) {
        printf("Cannot translate: Code contains variables or parameters of structure type.");
        return ts_error_flag;
    }
    if (with_ir_output) {
#ifdef _DEBUG
        output_file = strcatm(output_file, ".", "ir");
#endif
        FILE *f = fopen(output_file, "w+");
        if (f == NULL) assert(0);
        fputs(midCode, f);
        fclose(f);
    }
    return ts_error_flag;
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
    Node *compSt = find_brother(tree_node, _CompSt);
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
    tree_node = tree_node->child;
    Node *varDec = tree_node->child;
    while (varDec->type != _ID) varDec = varDec->child;
    char *varName = varDec->val.id;
    char *sm = get_mem(varName);
    if (find_brother(tree_node->child, _ASSIGNOP) != NULL) {
        char *t1 = new_tmp();
        char *exp = translate_Exp(find_brother(tree_node->child, _Exp), t1);
        char *s1 = strcatm(varName, " := ", t1);
        exp = strcatm(exp, "\n", s1);
        sm = strcatm(sm, "\n", exp);
    }
    Node *nbrDecList = find_brother(tree_node, _DecList);
    char *s2 = nbrDecList == NULL ? "" : translate_DecList(nbrDecList);
    return strcatm(sm, "\n", s2);
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

char *translate_Stmt(Node *tree_node) {
    tree_node = tree_node->child;
    // Exp SEMI
    if (tree_node->type == _Exp) {
        return translate_Exp(tree_node, NULL);
    }
    // CompSt
    else if (tree_node->type == _CompSt) {
        return translate_CompSt(tree_node);
    }
    // RETURN Exp SEMI
    else if (tree_node->type == _RETURN) {
        char *t1 = new_tmp();
        char *s1 = translate_Exp(find_brother(tree_node, _Exp), t1);
        return strcatm(s1, "\nRETURN ", t1);
    }
    // WHILE LP Exp RP Stmt1
    else if (tree_node->type == _WHILE) {
        char *label1 = new_label();
        char *label2 = new_label();
        char *label3 = new_label();
        char *s1 = translate_Cond(find_brother(tree_node, _Exp), label2, label3);
        char *s2 = translate_Stmt(find_brother(tree_node, _Stmt));
        char *ret = strcatm("LABEL", " ", label1);
        ret = strcatm(ret, " :\n", s1);
        ret = strcatm(ret, "\nLABEL ", label2);
        ret = strcatm(ret, " :\n", s2);
        ret = strcatm(ret, "\nGOTO ", label1);
        ret = strcatm(ret, "\nLABEL ", label3);
        ret = strcatm(ret, "", " :");
        return ret;
    }
    // IF ...
    char *label1 = new_label();
    char *label2 = new_label();
    char *label3 = new_label();
    char *s1 = translate_Cond(find_brother(tree_node, _Exp), label1, label2);
    Node *stmt = find_brother(tree_node, _Stmt);
    char *s2 = translate_Stmt(stmt);
    stmt = find_brother(stmt->brother, _Stmt);
    char *s3 = stmt == NULL ? "" : translate_Stmt(stmt);
    char *ret = strcatm(s1, "\nLABEL ", label1);
    ret = strcatm(ret, " :\n", s2);
    if (stmt != NULL) ret = strcatm(ret, "\nGOTO ", label3);
    ret = strcatm(ret, "\nLABEL ", label2);
    ret = strcatm(ret, "", " :");
    if (stmt != NULL) {
        ret = strcatm(ret, "\n", s3);
        ret = strcatm(ret, "\nLABEL ", label3);
        ret = strcatm(ret, "", " :");
    }
    return ret;
}

char *translate_Exp(Node *tree_node, char *place) {
    Node *expNode = tree_node;
    tree_node = tree_node->child;
    if (place == NULL) place = "t_";
    // INT FLOAT ID & funcall
    if (tree_node->type == _INT) {
        char *val = calloc(16, sizeof(char));
        sprintf(val, "%d", tree_node->val.i_val);
        return strcatm(place, " := #", val);
    } else if (tree_node->type == _FLOAT) {
        char *val = calloc(32, sizeof(char));
        sprintf(val, "%f", tree_node->val.f_val);
        return strcatm(place, " := #", val);
    } else if (tree_node->type == _ID) {
        if (tree_node->brother == NULL)
            return strcatm(place, " := ", tree_node->val.id);
        return translate_funcCall(tree_node, place);
    }
    // (exp) -exp !exp
    else if (tree_node->type == _LP) {
        char *t1 = new_tmp();
        char *s1 = translate_Exp(tree_node->brother, t1);
        char *s2 = strcatm(place, " := ", t1);
        return strcatm(s1, "\n", s2);
    } else if (tree_node->type == _MINUS) {
        char *t1 = new_tmp();
        char *s1 = translate_Exp(tree_node->brother, t1);
        char *s2 = strcatm(place, " := #0 - ", t1);
        return strcatm(s1, "\n", s2);
    } else if (tree_node->type == _NOT) {
        return translate_CondExp(expNode, place);
    }
    // exp ... exp
    Node *op = tree_node->brother;
    switch (op->type) {
    case _ASSIGNOP:
        return translate_AssExp(tree_node, place);
        break;
    case _AND:
    case _OR:
    case _RELOP:
        return translate_CondExp(expNode, place);
        break;
    case _PLUS:
    case _MINUS:
    case _STAR:
    case _DIV:
        return translate_CulExp(tree_node, place);
        break;
    case _LB: // arr[exp]
    {
        char *t1 = new_tmp();
        char *s1 = get_arrLocation(expNode, t1, malloc(sizeof(Type)));
        char *s2 = strcatm(place, " := *", t1);
        return strcatm(s1, "\n", s2);
        break;
    }
    default:
        ts_error_flag = 1;
        break;
    }
    return "";
}

char *translate_Cond(Node *tree_node, char *label_true, char *label_false) {
    Node *expNode = tree_node;
    tree_node = tree_node->child;
    if (tree_node->type == _NOT)
        return translate_Cond(tree_node->brother, label_false, label_true);
    if (tree_node->type == _Exp) {
        if (tree_node->brother->type == _RELOP) {
            char *t1 = new_tmp();
            char *t2 = new_tmp();
            char *s1 = translate_Exp(tree_node, t1);
            char *s2 = translate_Exp(tree_node->brother->brother, t2);
            char *op = relOP[tree_node->brother->val.i_val];
            char *s3 = strcatm("IF", " ", t1);
            s3 = strcatm(s3, " ", op);
            s3 = strcatm(s3, " ", t2);
            s3 = strcatm(s3, " GOTO ", label_true);
            s1 = strcatm(s1, "\n", s2);
            s1 = strcatm(s1, "\n", s3);
            s1 = strcatm(s1, "\nGOTO ", label_false);
            return s1;
        } else if (tree_node->brother->type == _AND) {
            char *label1 = new_label();
            char *s1 = translate_Cond(tree_node, label1, label_false);
            char *s2 = translate_Cond(tree_node->brother->brother, label_true, label_false);
            s1 = strcatm(s1, "\nLABEL ", label1);
            return strcatm(s1, " :\n", s2);
        } else if (tree_node->brother->type == _OR) {
            char *label1 = new_label();
            char *s1 = translate_Cond(tree_node, label_true, label1);
            char *s2 = translate_Cond(tree_node->brother->brother, label_true, label_false);
            s1 = strcatm(s1, "\nLABEL ", label1);
            return strcatm(s1, " :\n", s2);
        }
    }
    char *t1 = new_tmp();
    char *s1 = translate_Exp(expNode, t1);
    char *s2 = strcatm("IF", " ", t1);
    s2 = strcatm(s2, " != #0 GOTO ", label_true);
    s2 = strcatm(s2, "\nGOTO ", label_false);
    return strcatm(s1, "\n", s2);
}

char *translate_funcCall(Node *tree_node, char *place) {
    Node *args = find_brother(tree_node, _Args);
    if (args == NULL) {
        if (strcmp(tree_node->val.id, "read") == 0)
            return strcatm("READ", " ", place);
        return strcatm(place, " := CALL ", tree_node->val.id);
    }
    ArgsList *al = calloc(1, sizeof(ArgsList));
    al->next = NULL;
    char *s1 = translate_Args(find_brother(tree_node, _Args), al);
    al = al->next;
    if (strcmp(tree_node->val.id, "write") == 0) {
        char *s2 = strcatm("WRITE", " ", al->argName);
        s1 = strcatm(s1, "\n", s2);
        s2 = strcatm(place, " := ", "#0");
        s1 = strcatm(s1, "\n", s2);
        return s1;
    }
    char *s2 = strcatm("ARG", " ", al->argName);
    al = al->next;
    while (al != NULL) {
        s2 = strcatm(s2, "\nARG ", al->argName);
        al = al->next;
    }
    char *s3 = strcatm(place, " := CALL ", tree_node->val.id);
    s2 = strcatm(s2, "\n", s3);
    return strcatm(s1, "\n", s2);
}

char *translate_Args(Node *tree_node, ArgsList *argsList) {
    tree_node = tree_node->child;
    char *t1 = new_tmp();
    char *s1 = translate_Exp(tree_node, t1);
    ArgsList *newArg = calloc(1, sizeof(ArgsList));
    strcpy(newArg->argName, t1);
    newArg->next = argsList->next;
    argsList->next = newArg;
    Node *nbrArgs = find_brother(tree_node, _Args);
    char *s2 = nbrArgs == NULL ? "" : translate_Args(nbrArgs, argsList);
    return strcatm(s1, "\n", s2);
}

// expin
char *translate_CondExp(Node *tree_node, char *place) {
    char *label1 = new_label();
    char *label2 = new_label();
    char *s1 = strcatm(place, " := ", "#0");
    char *s2 = translate_Cond(tree_node, label1, label2);
    char *s3 = strcatm("LABEL", " ", label1);
    s3 = strcatm(s3, "", " :");
    char *s4 = strcatm(place, " := ", "#1");
    s3 = strcatm(s3, "\n", s4);
    char *s5 = strcatm("LABEL", " ", label2);
    s5 = strcatm(s5, "", " :");
    s1 = strcatm(s1, "\n", s2);
    s1 = strcatm(s1, "\n", s3);
    s1 = strcatm(s1, "\n", s5);
    return s1;
}

char *translate_AssExp(Node *tree_node, char *place) {
    if (tree_node->child->type == _ID) {
        char *t1 = new_tmp();
        char *s1 = translate_Exp(tree_node->brother->brother, t1);
        char *s2 = strcatm(tree_node->child->val.id, " := ", t1);
        char *s3 = strcatm(place, " := ", tree_node->child->val.id);
        s2 = strcatm(s2, "\n", s3);
        return strcatm(s1, "\n", s2);
    }
    if (tree_node->child->brother->type == _DOT) {
        ts_error_flag = 1;
        return "";
    }
    char *t1 = new_tmp();
    char *t2 = new_tmp();
    char *s1 = get_arrLocation(tree_node, t1, malloc(sizeof(Type)));
    char *s2 = translate_Exp(tree_node->brother->brother, t2);
    char *st = strcatm("*", "", t1);
    char *s3 = strcatm(st, " := ", t2);
    char *s4 = strcatm(place, " := ", st);
    s1 = strcatm(s1, "\n", s2);
    s1 = strcatm(s1, "\n", s3);
    s1 = strcatm(s1, "\n", s4);
    return s1;
}

char *translate_CulExp(Node *tree_node, char *place) {
    char op[2] = {0};
    switch (tree_node->brother->type) {
    case _PLUS:
        op[0] = '+';
        break;
    case _MINUS:
        op[0] = '-';
        break;
    case _STAR:
        op[0] = '*';
        break;
    case _DIV:
        op[0] = '/';
        break;
    default:
        break;
    }
    char *t1 = new_tmp();
    char *t2 = new_tmp();
    char *s1 = translate_Exp(tree_node, t1);
    char *s2 = translate_Exp(tree_node->brother->brother, t2);
    char *s3 = strcatm(place, " := ", t1);
    s3 = strcatm(s3, " ", op);
    s3 = strcatm(s3, " ", t2);
    s1 = strcatm(s1, "\n", s2);
    s1 = strcatm(s1, "\n", s3);
    return s1;
}

char *get_arrLocation(Node *tree_node, char *place, Type *eleType) {
    tree_node = tree_node->child;
    if (tree_node->type == _ID) {
        *eleType = read_sem_node(tree_node->val.id)->type;
        return strcatm(place, " := ", tree_node->val.id);
    }
    // t1 base pos
    char *t1 = new_tmp();
    char *s1 = get_arrLocation(tree_node, t1, eleType);
    // t2 expval
    char *t2 = new_tmp();
    char *s2 = translate_Exp(tree_node->brother->brother, t2);
    *eleType = (*eleType)->data.array.elem;
    int eleSz = size_of_arr(*eleType);
    char offs[32];
    sprintf(offs, "#%d", eleSz);
    // t3 tot offs
    char *t3 = new_tmp();
    char *s3 = strcatm(t3, " := ", t2);
    s3 = strcatm(s3, " * ", offs);
    char *s4 = strcatm(place, " := ", t1);
    s4 = strcatm(s4, " + ", t3);
    s1 = strcatm(s1, "\n", s2);
    s1 = strcatm(s1, "\n", s3);
    s1 = strcatm(s1, "\n", s4);
    return s1;
}

char *get_mem(char *varName) {
    Type t = read_sem_node(varName)->type;
    int sz = size_of_arr(t);
    if (sz == -1 && (ts_error_flag = 1)) return "";
    if (t->kind != ARRAY) return "";
    char szs[32];
    sprintf(szs, "%d", sz);
    char *t1 = new_tmp();
    char *s1 = strcatm("DEC", " ", t1);
    s1 = strcatm(s1, " ", szs);
    char *s2 = strcatm(varName, " := &", t1);
    return strcatm(s1, "\n", s2);
}

char *new_tmp() {
    char *s = malloc(32);
    sprintf(s, "t%d", tmpNo++);
    return s;
}

char *new_label() {
    char *s = malloc(32);
    sprintf(s, "label%d", labelNo++);
    return s;
}