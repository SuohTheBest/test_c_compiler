#include <string.h>
#include <malloc.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "generator.h"

#define NEXT_LINE   free(line_str);\
                    curr_line = curr_line->next;\
                    if(!curr_line)return;\
                    line_str = strdup(curr_line->line);\
                    token = next_token(line_str);

extern char *midCode;

ir_list_node ir_list;
ir_list_node *curr_func;
var_list_node var_list;
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
    curr_func = &ir_list;
}

void var_add_tail(int size, char *name) {
    var_list_node *p = &var_list;
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

void free_var_list() {
    var_list_node *p = &var_list, *next = var_list.next;
    free(p->name);
    while (next != NULL) {
        free(next->name);
        p = next;
        next = next->next;
        free(p);
    }
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
    while (strcmp(token, "FUNCTION") != 0 && token != NULL) {
        // read a line
        if (strcmp(token, "PARAM") == 0) {
            token = next_token(NULL);
            var_add_tail(4, token);
        } else if (strcmp(token, "DEC") == 0) {
            next_token(NULL);
            int size = atoi(next_token(NULL));
            NEXT_LINE
            var_add_tail(size, token);
        } else if (token[0] == 't') {
            // l-vals
            var_add_tail(4, token);
        }
        NEXT_LINE
    }
}

void generate_function() {

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
        free_var_list();
    }
    end:
    fclose(f);
}