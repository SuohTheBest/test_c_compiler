#include "semantic.h"

#define offset 17
char anonymous[] = "0_anonymous_";
int anonymous_cnt = 0;
int is_func_param = 0;
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
    printf("Error type %d at Line %d: %s.\n", kind, lineno, sem_error_text[kind]);
}

sem_node sem_type_map[1024];
sem_node sem_name_map[1024];

int add_type(char *name, Type type, int is_func_dec) {
    printf("add_type:%s\n", name);
    printType(type);
    unsigned index = hash_pjw(name);
    while (sem_type_map[index].name != NULL && strcmp(sem_type_map[index].name, name) != 0)index += offset;
    if (sem_type_map[index].name == NULL) {
        sem_type_map[index].name = name;
        sem_type_map[index].type = type;
        sem_type_map[index].is_func_dec = is_func_dec;
        return 0;
    } else {
        return -1;
    }
}

int add_name(char *name, Type type, int is_func_dec) {
    printf("add_name:%s\n", name);
    printType(type);
    unsigned index = hash_pjw(name);
    while (sem_name_map[index].name != NULL && strcmp(sem_name_map[index].name, name) != 0)index += offset;
    if (sem_name_map[index].name == NULL) {
        sem_name_map[index].name = name;
        sem_name_map[index].type = type;
        sem_name_map[index].is_func_dec = is_func_dec;
        return 0;
    } else {
        return -1;
    }
}

FieldList add_tail(Type t) {
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

sem_node *read_type(char *name) {
    unsigned index = hash_pjw(name);
    while (sem_type_map[index].name != NULL && strcmp(sem_type_map[index].name, name) != 0)index += offset;
    if (sem_type_map[index].name == NULL) return NULL;
    else return &sem_type_map[index];
}

sem_node *read_name(char *name) {
    unsigned index = hash_pjw(name);
    while (sem_name_map[index].name != NULL && strcmp(sem_name_map[index].name, name) != 0)index += offset;
    if (sem_name_map[index].name == NULL) return NULL;
    else return &sem_name_map[index];
}

int typeEqual(Type t1, Type t2) {
    if (t1 == NULL && t2 == NULL) return 1;
    if (t1 == NULL || t2 == NULL) return 0;
    if (t1->kind != t2->kind) return 0;

    switch (t1->kind) {
        case BASIC:
            return t1->data.basic == t2->data.basic;
        case ARRAY:
            return t1->data.array.size == t2->data.array.size &&
                   typeEqual(t1->data.array.elem, t2->data.array.elem);
        case STRUCTURE:
        case FUNCTION: {
            FieldList f1 = t1->data.field, f2 = t2->data.field;
            while (f1 && f2) {
                if (strcmp(f1->name, f2->name) != 0 || !typeEqual(f1->type, f2->type)) {
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

void sem_read_tree(Node *root) {
    // 从tree_root调用时是不可能 = _DefList/_Exp 的
    // 但我不想为read_CompSt再写一个这样的遍历函数，所以偷个懒
    if (root == NULL)return;
    if (root->type == _ExtDef) {
        read_ExtDef(root);
        sem_read_tree(root->brother);
    } else if (root->type == _DefList) {
        read_DefList(root, NULL);
        sem_read_tree(root->brother);
    } else if (root->type == _Exp) {
        read_Exp(root);
        sem_read_tree(root->brother);
    } else {
        sem_read_tree(root->child);
        sem_read_tree(root->brother);
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
        if (add_type(tag_name, struct_type, 0) != 0)
            sem_error(16, node->lineno);
        else
            return struct_type;
    } else {
        // 使用定义的 struct
        sem_node *type_node = read_type(tag_name);
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
    // 先检查return type是否一致，避免传参
    FieldList return_t = t->data.field;
    while (return_t->tail != NULL)return_t = return_t->tail;
    Node *pNode = find_node_subtree(node, _RETURN);
    if (pNode) {
        pNode = find_node(pNode, _Exp);
        Type actual_t = read_Exp(pNode).type;
        if (!typeEqual(actual_t, return_t->type))
            sem_error(8, pNode->lineno);
    }
    sem_read_tree(node);
}

Exp_Type read_Exp(Node *node) {
    node = node->child;
    Exp_Type ans;
    ans.type = NULL;
    ans.l_val = 0;
    ans.error = 1;
    if (node->type == _ID && node->brother == NULL) {
        sem_node *n = read_name(node->val.id);
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
        sem_node *n = read_name(node->val.id);
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
        Node *pNode = find_node(node, _Exp);
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
        if (!typeEqual(t1.type, t2.type)) {
            sem_error(7, node->lineno);
            return ans;
        }
        ans.type = t1.type;
    } else {
        // 赋值号
        Exp_Type t1 = read_Exp(node);
        if (t1.error)return ans;
        Node *pNode = find_node(node->brother, _Exp);
        Exp_Type t2 = read_Exp(pNode);
        if (t2.error)return ans;
        if (!t1.l_val)
            sem_error(6, node->lineno);
        if (!typeEqual(t1.type, t2.type))
            sem_error(5, node->lineno);
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
    Type func_type = read_FunDec(pNode);
    FieldList p_field = func_type->data.field;
    while (p_field->tail != NULL)p_field = p_field->tail;
    p_field->type = type;
    char *func_name = p_field->name;
    pNode = find_node(node, _CompSt);
    sem_node *prev_func = read_name(func_name);
    if (!pNode && prev_func != NULL) {
        if (!typeEqual(prev_func->type, func_type))sem_error(19, node->lineno);
        free(func_type);
        return;
    } else if (!pNode && prev_func == NULL) {
        add_name(func_name, func_type, 1);
        return;
    }
    // Specifier FunDec CompSt
    // e.g. int func(struct var v){...}
    if (prev_func != NULL) {
        if (!prev_func->is_func_dec) {
            sem_error(4, node->lineno);
            return;
        }
        if (!typeEqual(prev_func->type, func_type))sem_error(19, node->lineno);
        free(func_type);
        prev_func->is_func_dec = 0;
        return;
    }
    add_name(func_name, func_type, 0);
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
        is_func_param = 1;
        read_VarList(pNode, func_type);
        is_func_param = 0;
    }
    // 返回值type塞到field最后
    FieldList p_field = add_tail(func_type);
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
        if (!is_func_param && add_name(node->val.id, curr_t, 0) != 0)
            sem_error(3, node->lineno);
        if (t) {
            FieldList field = add_tail(t);
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
