#ifndef COMPILER_GENERATOR_H
#define COMPILER_GENERATOR_H

typedef struct ir_list_node {
    char *line;
    struct ir_list_node *next;
} ir_list_node;

typedef struct var_list_node {
    char* name;
    int size;
    struct var_list_node *next;
} var_list_node;

void generate_mips(char *output_file);

int reg(char *name);

void re_reg(char *name, int reg);

void scan_local_var();

void generate_function();

#endif //COMPILER_GENERATOR_H
