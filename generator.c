#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include "generator.h"

#define NEXT_LINE   free(line_str);\
                    curr_line = curr_line->next;\
                    if(curr_line){ \
                        line_str = strdup(curr_line->line);\
                        token = next_token(line_str);      \
                    }

extern char *midCode;

ir_list_node ir_list;
ir_list_node *curr_func;
var_list_node var_list;
var_list_node param_list;
FILE *f;
int reg_counter = 1;

void split_ir() {
    char *line = strtok(midCode, "\n");
    ir_list.line = line;
    ir_list_node *p = &ir_list;
    line = strtok(NULL, "\n");
    while (line != NULL) {
        p->next = malloc(sizeof(ir_list_node));
        p = p->next;
        p->line = line;
        line = strtok(NULL, "\n");
    }
    p->next = NULL;
    curr_func = &ir_list;
}

void var_add_tail(var_list_node *head, int size, char *name) {
    var_list_node *p = head;
    while (p->next != NULL) {
        p = p->next;
        if (strcmp(p->name, name) == 0)return;
    }
    p->next = malloc(sizeof(var_list_node));
    p->next->size = size;
    p->next->name = strdup(name);
    p->next->next = NULL;
}

int var_find(char *name) {
    int offset = 0;
    var_list_node *p = &var_list;
    while (var_list.next != NULL) {
        p = p->next;
        if (strcmp(p->name, name) == 0)return offset;
        offset += p->size;
    }
    assert(0);
}

void free_var_list(var_list_node *head) {
    var_list_node *p = head->next, *next;
    while (p != NULL) {
        next = p->next;
        free(p->name);
        free(p);
        p = next;
    }
    head->next = NULL;
    head->size = 0;
}

int reg(char *name) {

}

void re_reg(char *name, int reg) {

}

char *next_token(char *line) {
    return strtok(line, " ");
}

void scan_local_var() {
    ir_list_node *curr_line = curr_func;
    char *line_str = strdup(curr_line->line);
    char *token = next_token(line_str);
    token = next_token(NULL);//func_name
    var_list.name = strdup(token);
    NEXT_LINE
    while (curr_line != NULL && strcmp(token, "FUNCTION") != 0) {
        // read a line
        if (strcmp(token, "PARAM") == 0) {
            token = next_token(NULL);
            var_add_tail(&param_list, 4, token);
        } else if (strcmp(token, "DEC") == 0) {
            next_token(NULL);
            int size = atoi(next_token(NULL));
            NEXT_LINE
            var_add_tail(&var_list, size, token);
        } else if (token[0] == 't') {
            // l-vals
            var_add_tail(&var_list, 4, token);
        }
        NEXT_LINE
    }
    int size = 0;
    var_list_node *p = &var_list;
    while (p->next != NULL) {
        p = p->next;
        size += p->size;
    }
    var_list.size = size + 8;
}

void generate_function() {
    fprintf(f, "%s:\n", var_list.name);
    fprintf(f, "# function init\n");
    int stack_size = var_list.size;
    fprintf(f, "addiu   $sp,$sp,-%d\n"
               "sw      $31,%d($sp)\n"
               "sw      $fp,%d($sp)\n"
               "move    $fp,$sp\n", stack_size, stack_size - 4, stack_size - 8);
    ir_list_node *curr_line = curr_func->next;
    char *line_str = strdup(curr_line->line);
    char *token = next_token(line_str);
    while (curr_line != NULL && strcmp(token, "FUNCTION") != 0) {
        // todo
        NEXT_LINE
    }
    fprintf(f, "\n");
    curr_func = curr_line;
}

void generate_mips(char *output_file) {
    split_ir();
    f = fopen(output_file, "w+");
    if (f == NULL) assert(0);
    char op[16];
    while (1) {
        if (!curr_func)break;
        sscanf(curr_func->line, "%s", op);
        while (strcmp(op, "FUNCTION") != 0) {
            curr_func = curr_func->next;
            if (!curr_func)goto end;
            sscanf(curr_func->line, "%s", op);
        }
        scan_local_var();
        generate_function();
        free_var_list(&var_list);
        free_var_list(&param_list);
    }
    end:
    fclose(f);
}