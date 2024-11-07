#include "semantic.h"

#define offset 17
#define NEW_FIELD_INIT(field_name)      (field_name)->tail = malloc(sizeof(struct FieldList_));\
                                        (field_name) = (field_name)->tail;

char anonymous[] = "0_anonymous_";
int anonymous_cnt = 0;
char *tmp_strs[64];
int tmp_nums[64];
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
                               "Multiple declaration of function"};

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

int add_type(char *name, Type type, int is_func_def) {
    printf("add_type:%s\n", name);
    unsigned index = hash_pjw(name);
    while (sem_type_map[index].name != NULL && strcmp(sem_type_map[index].name, name) != 0)index += offset;
    if (sem_type_map[index].name == NULL) {
        sem_type_map[index].name = name;
        sem_type_map[index].type = type;
        sem_type_map[index].is_func_def = is_func_def;
        return 0;
    } else {
        return -1;
    }
}

int add_name(char *name, Type type, int is_func_def) {
    printf("add_name:%s\n", name);
    unsigned index = hash_pjw(name);
    while (sem_name_map[index].name != NULL && strcmp(sem_name_map[index].name, name) != 0)index += offset;
    if (sem_name_map[index].name == NULL) {
        sem_name_map[index].name = name;
        sem_name_map[index].type = type;
        sem_name_map[index].is_func_def = is_func_def;
        return 0;
    } else {
        return -1;
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

void sem_read_tree(Node *root) {
    if (root == NULL)return;
    if (root->type == _ExtDef) {
        read_ExtDef(root);
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

Type read_Specifier(Node *node) {
    node = node->child;
    // TYPE
    if (node->type == _TYPE) {
        if (node->val.i_val == 0) return &int_type;
        else return &float_type;
    } else {
        // StructSpecifier = tag + deflist
        node = node->child;
        Node *tag = find_node(node, _Tag);
        char *tag_name;
        if (tag == NULL)tag = find_node(node, _OptTag);
        if (tag)tag_name = tag->child->val.id;
        else {
            tag_name = malloc(64 * sizeof(char));
            memset(tag_name, 0, 64 * sizeof(char));
            strcat(tag_name, anonymous);
            tag_name[12] = '0' + anonymous_cnt++;
            tag_name[13] = '\0';
        }
        Type struct_type = malloc(sizeof(struct Type_));
        struct_type->kind = STRUCTURE;
        struct_type->data.structure = malloc(sizeof(struct FieldList_));
        Node *def_list = find_node(node, _DefList);
        if (def_list)read_DefList(def_list, struct_type->data.structure);
        if (add_type(tag_name, struct_type, 0) != 0)
            sem_error(16, node->lineno);
        else
            return struct_type;
    }
    return NULL;
}

void read_ExtDecList(Node *node, Type type) {
    node = node->child;
    if (node->type == _VarDec)read_VarDec(node, type, NULL);
    Node *next = find_node(node, _ExtDecList);
    if (next) read_ExtDecList(next, type);
}

void read_ExtDef(Node *node) {
    node = node->child;
    Type type = read_Specifier(node);
    // Specifier ExtDecList SEMI
    Node *extdec_list = find_node(node, _ExtDecList);
    if (extdec_list)read_ExtDecList(extdec_list, type);
    // Specifier SEMI
    // Specifier FunDec CompSt

    // Specifier FunDec SEMI
}

void read_DecList(Node *node, Type type, FieldList struct_field) {
    node = node->child;
    // Dec COMMA DecList
    if (struct_field) {
        // error type 15
        Node *vardec = node->child;
        if (vardec->brother != NULL)sem_error(15, vardec->lineno);
        read_VarDec(vardec, type, struct_field);
        NEW_FIELD_INIT(struct_field)
    }
    Node *next = find_node(node, _DecList);
    if (next) read_DecList(next, type, struct_field);
}

void read_VarDec(Node *node, Type type, FieldList struct_field) {
    node = node->child;
    // ID
    if (node->type == _ID) {
        if (add_name(node->val.id, type, 0) != 0)
            sem_error(3, node->lineno);
        if (struct_field) {
            struct_field->type = type;
            struct_field->name = node->val.id;
        }
    } else {
        Node *vardec = find_node(node, _VarDec);
        int size = find_node(node, _INT)->val.i_val;
        Type arr_type = malloc(sizeof(struct Type_));
        arr_type->kind = ARRAY;
        arr_type->data.array.elem = type;
        arr_type->data.array.size = size;
        read_VarDec(vardec, arr_type, struct_field);
    }
}

void read_DefList(Node *node, FieldList field) {
    node = node->child;
    if (node->type == _Def)read_Def(node, field);
    Node *next = find_node(node, _DefList);
    if (next) {
        if (field) read_DefList(next, field->tail);
        else read_DefList(next, NULL);
    }
}

void read_Def(Node *node, FieldList field) {
    node = node->child;
    // Specifier DecList SEMI
    Node *specifier = find_node(node, _Specifier);
    Type type = NULL;
    if (specifier) type = read_Specifier(specifier);
    if (!type)return;
    Node *dec_list = find_node(node, _DecList);
    if (dec_list) read_DecList(dec_list, type, field);
}
