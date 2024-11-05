#ifndef COMPILER_SEMANTIC_H
#define COMPILER_SEMANTIC_H

typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;

struct Type_ {
    enum {
        BASIC, ARRAY, STRUCTURE, FUNCTION
    } kind;
    union {
        enum {
            _FLOAT, _INT
        } basic;
        struct {
            Type elem;
            int size;
        } array;
        FieldList structure;
        FieldList function;
    } u;
};

struct FieldList_ {
    char *name;
    Type type;
    FieldList tail;
};

typedef struct type_node {
    char name[32];
    struct Type_ type;
    bool is_func_def;
} type_node;


unsigned hash_pjw(char *name);


#endif //COMPILER_SEMANTIC_H