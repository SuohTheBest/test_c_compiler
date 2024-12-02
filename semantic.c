#include "semantic.h"

#define offset 17
char anonymous[] = "0_anonymous_";
int anonymous_cnt = 0;
int write_enable = 1;
int last_err_kind = 0, last_err_lineno = 0;
char sem_error_text[20][64] = {"Unknown Error",
                               "Undefined variable",
                               "Undefined function",
                               "Multiple definition of variable",
                               "Multiple definition of function",
                               "Expression type unmatched",
                               "r-val in left expression",
                               "Unmatched operand type",
                               "Unmatched return type and declaration",
                               "Unmatched parameter type or number",
                               "[] used on a non-array variable",
                               "() used on a common variable",
                               "Non-integer in []",
                               ". used on a non-struct variable",
                               "Accessing an undefined field in struct",
                               "Multiple definition or init of field in struct",
                               "Multiple definition of struct name",
                               "Init a variable with an undefined struct",
                               "Function declaration without definition",
                               "Multiple or conflict declaration of function"};

struct Type_ int_type = {.kind=BASIC, .data=1};
struct Type_ float_type = {.kind=BASIC, .data=0};

unsigned hash_pjw(char *name) {
    unsigned val = 0, i;
    for (; *name; ++name) {
        val = (val << 2) + *name;
        if ((i = val & ~0x400)) val = (val ^ (i >> 12)) & 0x400;
    }
    return val;
}

void sem_error(int kind, int lineno) {
    if (kind == last_err_kind && lineno == last_err_lineno)return;
    last_err_kind = kind;
    last_err_lineno = lineno;
    printf("Error type %d at Line %d: %s.\n", kind, lineno, sem_error_text[kind]);
}

sem_node sem_map[1024];

int add_sem_node(char *name, Type type, int func_dec_lineno) {
//    printf("add_sem_node:%s\n", name);
//    printType(type);
    unsigned index = hash_pjw(name);
    while (sem_map[index].name != NULL && strcmp(sem_map[index].name, name) != 0)index += offset;
    if (sem_map[index].name == NULL) {
        sem_map[index].name = name;
        sem_map[index].type = type;
        sem_map[index].func_dec_lineno = func_dec_lineno;
        return 0;
    } else {
        return -1;
    }
}

FieldList create_tail_field(Type t) {
    FieldList p = t->data.field;
    if (!p) {
        t->data.field = calloc(1, sizeof(struct FieldList_));
        p = t->data.field;
        return p;
    } else {
        while (p->tail != NULL)p = p->tail;
        p->tail = calloc(1, sizeof(struct FieldList_));
        return p->tail;
    }
}

sem_node *read_sem_node(char *name) {
    unsigned index = hash_pjw(name);
    while (sem_map[index].name != NULL && strcmp(sem_map[index].name, name) != 0)index += offset;
    if (sem_map[index].name == NULL) return NULL;
    else return &sem_map[index];
}

int typeEqual(Type t1, Type t2) {
    if (t1 == t2) return 1;
    if (t1 == NULL || t2 == NULL) return 0;
    if (t1->kind != t2->kind) return 0;
    switch (t1->kind) {
        case BASIC:
            return t1->data.basic == t2->data.basic;
        case ARRAY: {
            while (t1->kind == ARRAY && t2->kind == ARRAY) {
                t1 = t1->data.array.elem;
                t2 = t2->data.array.elem;
            }
            return typeEqual(t1, t2);
        }
        case STRUCTURE: {
            return t1 == t2;
        }
        case FUNCTION: {
            FieldList f1 = t1->data.field, f2 = t2->data.field;
            while (f1 && f2) {
                if (!typeEqual(f1->type, f2->type)) {
                    return 0;
                }
                f1 = f1->tail;
                f2 = f2->tail;
            }
            return f1 == NULL && f2 == NULL;
        }
        default:
            return 0;
    }
}

void printType(Type t) {
    if (t == NULL) {
        printf("NULL\n");
        return;
    }
    switch (t->kind) {
        case BASIC:
            if (t->data.basic)printf("INT\n");
            else printf("FLOAT\n");
            break;
        case ARRAY:
            printf("ARRAY : size = %d, element type = ", t->data.array.size);
            printType(t->data.array.elem);
            break;
        case STRUCTURE:
            printf("STRUCTURE :\n");
            for (FieldList f = t->data.field; f; f = f->tail) {
                printf("  Field name: %s, Field type: ", f->name);
                printType(f->type);
            }
            break;
        case FUNCTION:
            printf("FUNCTION Type:\n");
            for (FieldList f = t->data.field; f; f = f->tail) {
                printf("  Parameter name: %s, Parameter type: ", f->name);
                printType(f->type);
            }
            break;
        default:
            printf("Unknown Type\n");
    }
}

void sem_read_tree(Node *root, FieldList f) {
    // 从tree_root调用时是不可能 = _DefList/_Exp 的
    // 但我不想为read_CompSt再写一个这样的遍历函数，所以偷个懒
    if (root == NULL)return;
    if (root->type == _ExtDef) {
        read_ExtDef(root);
        sem_read_tree(root->brother, f);
    } else if (root->type == _DefList) {
        read_DefList(root, NULL);
        sem_read_tree(root->brother, f);
    } else if (root->type == _RETURN) {
        Node *pNode = find_node(root, _Exp);
        Exp_Type actual_t = read_Exp(pNode);
        if (!actual_t.error && !typeEqual(actual_t.type, f->type))
            sem_error(8, pNode->lineno);
        sem_read_tree(root->brother, f);
    } else if (root->type == _Exp) {
        read_Exp(root);
        sem_read_tree(root->brother, f);
    } else {
        sem_read_tree(root->child, f);
        sem_read_tree(root->brother, f);
    }
}

void semantic_analysis(Node *root) {
    Type t_read, t_write;
    t_read = calloc(1, sizeof(struct Type_));
    t_write = calloc(1, sizeof(struct Type_));
    t_read->kind = FUNCTION;
    t_write->kind = FUNCTION;
    FieldList f_read = create_tail_field(t_read);
    f_read->name = "read";
    f_read->type = &int_type;
    FieldList f1_write = create_tail_field(t_write);
    f1_write->type = &int_type;
    FieldList f2_write = create_tail_field(t_write);
    f2_write->name = "write";
    f2_write->type = &int_type;
    add_sem_node("read", t_read, 0);
    add_sem_node("write", t_write, 0);
    sem_read_tree(root, NULL);
    // 检查声明未定义
    for (int i = 0; i < 1024; ++i) {
        if (sem_map[i].type && sem_map[i].type->kind == FUNCTION && sem_map[i].func_dec_lineno) {
            sem_error(18, sem_map[i].func_dec_lineno);
        }
    }
}

Node *find_node(Node *node, enum type_t type) {
    while (node != NULL && node->type != type) node = node->brother;
    return node; // either NULL or correct.
}

Node *find_node_subtree(Node *node, enum type_t type) {
    if (node == NULL || node->type == type) return node;
    Node *result = find_node_subtree(node->child, type);
    if (result != NULL) return result;
    return find_node_subtree(node->brother, type);
}

Type check_func_call(Node *node, FieldList f) {
    if (f == NULL)return NULL;
    if (node == NULL) {
        if (f->tail == NULL)return f->type;
        else return NULL;
    }
    node = node->child;
    Type curr = read_Exp(node).type;
    if (!typeEqual(curr, f->type))return 0;
    Node *next = find_node(node, _Args);
    return check_func_call(next, f->tail);
}

Type read_Specifier(Node *node) {
    node = node->child;
    // basic types
    if (node->type == _TYPE) {
        if (node->val.i_val == 0) return &int_type;
        else return &float_type;
    }
    // struct types
    node = node->child;
    Node *tag = find_node(node, _Tag);
    char *tag_name;
    if (tag == NULL)tag = find_node(node, _OptTag);
    if (tag)tag_name = tag->child->val.id;
    else {
        tag_name = calloc(1, 64 * sizeof(char));
        memset(tag_name, 0, 64 * sizeof(char));
        strcat(tag_name, anonymous);
        tag_name[12] = '0' + anonymous_cnt++;
        tag_name[13] = '\0';
    }
    Node *def_list = find_node(node, _DefList);
    if (def_list) {
        // struct 定义
        Type struct_type = calloc(1, sizeof(struct Type_));
        struct_type->kind = STRUCTURE;
        read_DefList(def_list, struct_type);
        if (add_sem_node(tag_name, struct_type, 0) != 0)
            sem_error(16, node->lineno);
        else
            return struct_type;
    } else {
        // 使用定义的 struct
        sem_node *type_node = read_sem_node(tag_name);
        if (type_node)
            return type_node->type;
        else
            sem_error(17, node->lineno);
    }
    return NULL;
}

void read_CompSt(Node *node, Type t) {
    // 函数里的所有语句 (DefList + StmtList)
    node = node->child;
    // 悲报：检查return type是否一致仍然需要传参
    FieldList return_t = t->data.field;
    while (return_t->tail != NULL)return_t = return_t->tail;
    // 可能存在多个return分支
    sem_read_tree(node, return_t);
}

Exp_Type read_Exp(Node *node) {
    node = node->child;
    Exp_Type ans;
    ans.type = NULL;
    ans.l_val = 0;
    ans.error = 1;
    if (node->type == _ID && node->brother == NULL) {
        sem_node *n = read_sem_node(node->val.id);
        if (!n) {
            sem_error(1, node->lineno);
            return ans;
        }
        ans.type = n->type;
        ans.l_val = 1;
    } else if (node->type == _INT)
        ans.type = &int_type;
    else if (node->type == _FLOAT)
        ans.type = &float_type;
    else if (node->type == _ID) {
        // 函数调用
        sem_node *n = read_sem_node(node->val.id);
        if (!n) {
            sem_error(2, node->lineno);
            return ans;
        }
        if (n->type->kind != FUNCTION) {
            sem_error(11, node->lineno);
            return ans;
        }
        Node *pNode = find_node(node, _Args);
        ans.type = check_func_call(pNode, n->type->data.field);
        if (ans.type == NULL) {
            sem_error(9, node->lineno);
            return ans;
        }
    } else if (node->type == _Exp && node->brother->type == _LB) {
        // 访问数组
        Exp_Type t1 = read_Exp(node);
        if (t1.error) return ans;
        if (t1.type->kind != ARRAY) {
            sem_error(10, node->lineno);
            return ans;
        }
        Node *pNode = find_node(node->brother, _Exp);
        Exp_Type t2 = read_Exp(pNode);
        if (t2.error)return ans;
        if (t2.type != &int_type) {
            sem_error(12, node->lineno);
            return ans;
        }
        ans.type = t1.type->data.array.elem;
        ans.l_val = 1;
    } else if (node->type == _Exp && node->brother->type == _DOT) {
        // 访问struct
        Exp_Type t1 = read_Exp(node);
        if (t1.error)return ans;
        if (t1.type->kind != STRUCTURE) {
            sem_error(13, node->lineno);
            return ans;
        }
        Node *pNode = find_node(node, _ID);
        char *field_name = pNode->val.id;
        FieldList f = t1.type->data.field;
        while (f != NULL && strcmp(f->name, field_name) != 0) f = f->tail;
        if (f == NULL) {
            sem_error(14, node->lineno);
            return ans;
        }
        ans.type = f->type;
        ans.l_val = 1;
    } else if (node->type == _LP) {
        Node *pNode = find_node(node, _Exp);
        return read_Exp(pNode);
    } else if (node->type != _Exp) {
        Node *pNode = find_node(node, _Exp);
        ans = read_Exp(pNode);
        ans.l_val = 0;
    } else if (node->brother->type != _ASSIGNOP) {
        Exp_Type t1 = read_Exp(node);
        if (t1.error)return ans;
        Node *pNode = find_node(node->brother, _Exp);
        Exp_Type t2 = read_Exp(pNode);
        if (t2.error)return ans;
        pNode = node->brother;
        if ((t1.type != &int_type && t1.type != &float_type) || !typeEqual(t1.type, t2.type)) {
            sem_error(7, node->lineno);
            return ans;
        }
        if (pNode->type == _AND || pNode->type == _OR || pNode->type == _RELOP)
            ans.type = &int_type;
        else
            ans.type = t1.type;
    } else {
        // 赋值号
        Exp_Type t1 = read_Exp(node);
        if (t1.error)return ans;
        Node *pNode = find_node(node->brother, _Exp);
        Exp_Type t2 = read_Exp(pNode);
        if (t2.error)return ans;
        if (!t1.l_val) {
            sem_error(6, node->lineno);
            return ans;
        }
        if (!typeEqual(t1.type, t2.type)) {
            sem_error(5, node->lineno);
            return ans;
        }
        ans.type = t1.type;
    }
    ans.error = 0;
    return ans;
}

void read_ExtDecList(Node *node, Type t) {
    node = node->child;
    if (node->type == _VarDec)read_VarDec(node, t, NULL);
    Node *next = find_node(node, _ExtDecList);
    if (next) read_ExtDecList(next, t);
}

void read_ExtDef(Node *node) {
    node = node->child;
    Type type = read_Specifier(node);
    // Specifier ExtDecList SEMI
    // e.g. struct s {...};
    Node *pNode = find_node(node, _ExtDecList);
    if (pNode) {
        read_ExtDecList(pNode, type);
        return;
    }
    // Specifier SEMI
    // e.g. struct s;
    pNode = find_node(node, _FunDec);
    if (!pNode)return;
    // Specifier FunDec SEMI
    // e.g. int func(struct var v);
    Node *compSt = find_node(node, _CompSt);
    Type func_type = NULL;
    if (!compSt) {
        write_enable = 0;
        func_type = read_FunDec(pNode);
        write_enable = 1;
    } else
        func_type = read_FunDec(pNode);
    FieldList p_field = func_type->data.field;
    while (p_field->tail != NULL)p_field = p_field->tail;
    p_field->type = type;
    char *func_name = p_field->name;
    pNode = find_node(node, _CompSt);
    sem_node *prev_func = read_sem_node(func_name);
    if (!pNode && prev_func != NULL) {
        if (!typeEqual(prev_func->type, func_type))sem_error(19, node->lineno);
        free(func_type);
        return;
    } else if (!pNode && prev_func == NULL) {
        add_sem_node(func_name, func_type, node->lineno);
        return;
    }
    // Specifier FunDec CompSt
    // e.g. int func(struct var v){...}
    if (prev_func != NULL) {
        if (!prev_func->func_dec_lineno) {
            sem_error(4, node->lineno);
            return;
        }
        if (!typeEqual(prev_func->type, func_type)) {
            sem_error(19, node->lineno);
            return;
        }
        free(func_type);
        prev_func->func_dec_lineno = 0;
        return;
    }
    add_sem_node(func_name, func_type, 0);
    read_CompSt(pNode, func_type);
}

void read_VarList(Node *node, Type t) {
    node = node->child;
    // ParamDec (COMMA VarList)
    Node *pNode = find_node(node, _ParamDec);
    read_ParamDec(pNode, t);
    pNode = find_node(node, _VarList);
    if (pNode) {
        read_VarList(pNode, t);
    }
}

void read_ParamDec(Node *node, Type t) {
    node = node->child;
    // Specifier VarDec
    // e.g. int a = 0
    Node *pNode = find_node(node, _Specifier);
    Type spec = read_Specifier(pNode);
    pNode = find_node(node, _VarDec);
    read_VarDec(pNode, spec, t);
}

Type read_FunDec(Node *node) {
    node = node->child;
    // ID + (VarList)
    char *func_name;
    Node *pNode = find_node(node, _ID);
    func_name = pNode->val.id;
    Type func_type = calloc(1, sizeof(struct Type_));
    func_type->kind = FUNCTION;
    pNode = find_node(node, _VarList);
    if (pNode) {
        read_VarList(pNode, func_type);
    }
    // 返回值type塞到field最后
    FieldList p_field = create_tail_field(func_type);
    p_field->name = func_name;
    return func_type;
}

void read_DecList(Node *node, Type curr_t, Type t) {
    node = node->child;
    // Dec COMMA DecList
    // e.g. a = 0,b,c,d
    // curr_t 是这些变量的type, t是function/struct, 如果存在, 需要add_tail这些变量
    Node *vardec = node->child;
    if (t) {
        // error type 15
        // 不允许在struct/function里赋值
        if (vardec->brother != NULL)sem_error(15, vardec->lineno);
    }
    read_VarDec(vardec, curr_t, t);
    Node *exp = find_node(vardec, _Exp);
    if (!t && exp) {
        Exp_Type expType = read_Exp(exp);
        if (!expType.error && !typeEqual(curr_t, expType.type))
            sem_error(5, exp->lineno);
    }
    Node *next = find_node(node, _DecList);
    if (next) {
        read_DecList(next, curr_t, t);
    }
}

void read_VarDec(Node *node, Type curr_t, Type t) {
    node = node->child;
    // e.g. a[10][10]
    if (node->type == _ID) {
        // 变量重复定义
        if (write_enable && add_sem_node(node->val.id, curr_t, 0) != 0) {
            if (t && t->kind == STRUCTURE)sem_error(15, node->lineno);
            else sem_error(3, node->lineno);
        }
        if (t) {
            FieldList field = create_tail_field(t);
            field->type = curr_t;
            field->name = node->val.id;
        }
        return;
    }
    Node *vardec = find_node(node, _VarDec);
    int size = find_node(node, _INT)->val.i_val;
    Type arr_type = calloc(1, sizeof(struct Type_));
    arr_type->kind = ARRAY;
    arr_type->data.array.elem = curr_t;
    arr_type->data.array.size = size;
    read_VarDec(vardec, arr_type, t);
}

void read_DefList(Node *node, Type t) {
    node = node->child;
    if (node->type == _Def)read_Def(node, t);
    Node *next = find_node(node, _DefList);
    if (next)
        read_DefList(next, t);
}

void read_Def(Node *node, Type t) {
    node = node->child;
    // Specifier DecList SEMI
    // e.g. int a,b;
    Node *specifier = find_node(node, _Specifier);
    Type type = NULL;
    if (specifier) type = read_Specifier(specifier);
    if (!type)return;
    Node *dec_list = find_node(node, _DecList);
    if (dec_list) read_DecList(dec_list, type, t);
}
