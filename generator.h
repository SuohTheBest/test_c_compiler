#ifndef COMPILER_GENERATOR_H
#define COMPILER_GENERATOR_H

typedef struct ir_list_node {
    char *line;
    struct ir_list_node *next;
} ir_list_node;

typedef struct var_list_node {
    int size;
    char *name;
    struct var_list_node *next;
} var_list_node;

void generate_mips(char *midCode, char *output_file);

void generate_preCode();

void split_ir(char *midCode);

void scan_local_var(ir_list_node *code);

int var_add_tail(var_list_node *head, int size, char *name);

void generate_function(ir_list_node *code);

int reg(char *name);

int var_offset(char *var_name);

void re_reg(char *name, int reg, int need_write_back);

ir_list_node *generate_funcall(ir_list_node *code);

void generate_assign(ir_list_node *code);

void generate_if(ir_list_node *code);

#endif // COMPILER_GENERATOR_H
