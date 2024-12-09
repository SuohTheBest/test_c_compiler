#include "generator.h"
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

ir_list_node *ir_list;
var_list_node *var_list;
var_list_node *param_list;
FILE *out_put_file;
int reg_counter = 1;

char *next_token(char *line) {
    return strtok(line, " ");
}

void generate_mips(char *midCode, char *output_file) {
    out_put_file = fopen(output_file, "w+");
    if (out_put_file == NULL) assert(0);
    split_ir(midCode);
    char op[64];
    ir_list_node *p = ir_list;
    while (p != NULL) {
        sscanf(p->line, "%s", op);
        if (strcmp(op, "FUNCTION") != 0) {
            scan_local_var(p);
            generate_function(p);
        }
        p = p->next;
    }
    fclose(out_put_file);
}

void split_ir(char *midCode) {
    ir_list_node *p = ir_list = calloc(1, sizeof(ir_list_node));
    p->line = "head_node";
    char *line = strtok(midCode, "\n");
    while (line != NULL) {
        p->next = calloc(1, sizeof(ir_list_node));
        p = p->next;
        p->line = line;
        line = strtok(NULL, "\n");
    }
    p->next = NULL;
}

void scan_local_var(ir_list_node *code) {
    char *line_str = strdup(code->line);
    char *token = next_token(line_str);
    token = next_token(NULL); // func_name
    var_list = calloc(1, sizeof(var_list_node));
    var_list->name = strdup(token);
    var_list->next = NULL;
    var_list->size = 8;
    param_list = calloc(1, sizeof(var_list_node));
    param_list->name = "head_node";
    param_list->next = NULL;
    param_list->size = 0;
    code = code->next;
    while (code != NULL) {
        line_str = strdup(code->line);
        token = next_token(line_str);
        if (strcmp(token, "FUNCTION") == 0) break;
        if (strcmp(token, "PARAM") == 0) {
            token = next_token(NULL);
            var_add_tail(param_list, 4, token);
        } else if (strcmp(token, "DEC") == 0) {
            token = next_token(NULL);
            int size = atoi(next_token(NULL));
            var_list->size += var_add_tail(var_list, size, token);
        } else if (strcmp(token, "ARG") == 0) {
            var_list->size += 4;
        } else if (strcmp(next_token(NULL), ":=") == 0) {
            var_list->size += var_add_tail(var_list, 4, token);
        }
        code = code->next;
    }
}

int var_add_tail(var_list_node *head, int size, char *name) {
    if (name[0] == '*') return 0;
    var_list_node *p = head;
    while (p->next != NULL) {
        if (strcmp(p->next->name, name) == 0) return 0;
        p = p->next;
    }
    p->next = calloc(1, sizeof(var_list_node));
    p->next->size = size;
    p->next->name = strdup(name);
    p->next->next = NULL;
    return size;
}

void generate_function(ir_list_node *code) {
    fprintf(out_put_file, "%s:\n", var_list->name);
    fprintf(out_put_file, "# function init\n");
    int frame_size = var_list->size;
    fprintf(out_put_file, "subu    $sp,$sp,%d\n"
                          "sw      $ra,%d($sp)\n"
                          "sw      $fp,%d($sp)\n"
                          "move    $fp,$sp\n",
            frame_size, frame_size - 4, frame_size - 8);
    code = code->next;
    while (code != NULL) {
        char *line_str = strdup(code->line);
        char *token = next_token(line_str);
        if (strcmp(token, "FUNCTION") == 0) break;
        if (strcmp(token, "PARAM") == 0 || strcmp(token, "DEC") == 0) {
            code = code->next;
            continue;
        }
        if (strcmp(token, "LABEL") == 0) {
            token = next_token(NULL);
            fprintf(out_put_file, "%s:\n", token);
        } else if (strcmp(token, "GOTO") == 0) {
            token = next_token(NULL);
            fprintf(out_put_file, "j %s\n", token);
        } else if (strcmp(token, "RETURN") == 0) {
            generate_return(code);
        } else if (strcmp(token, "IF") == 0) {
            generate_if(code);
        } else if (strcmp(token, "READ") == 0) {
            generate_read(code);
        } else if (strcmp(token, "WRITE") == 0) {
            generate_write(code);
        } else if (strcmp(token, "ARG") == 0) {
            code = generate_funcall(code);
        } else if (strcmp(next_token(NULL), ":=") == 0) {
            generate_assign(code);
        }
        code = code->next;
    }
    fprintf(out_put_file, "move    $sp,$fp\n"
                          "lw      $ra,%d($sp)\n"
                          "lw      $fp,%d($sp)\n"
                          "addiu   $sp,$sp,%d\n"
                          "jr      $ra\n",
            frame_size - 4, frame_size - 8, frame_size);
    fprintf(out_put_file, "\n");
}

void generate_assign(ir_list_node *code) {
    char *line_str = strdup(code->line);
    char *token = next_token(line_str);
    if (strcmp(token, "t_") == 0) return;
    if (token[0] == '*') {
        genAssign_leftStar(code);
        return;
    }
    char *var0 = token;
    token = next_token(NULL);
    token = next_token(NULL);
    if (strcmp(token, "CALL") == 0) {
        generate_funcall(code);
        return;
    }
    char *var1 = token;
    token = next_token(NULL);
    if (token == NULL) {
        int reg0 = reg(var0);
        int reg1 = reg(var1);
        // todo
        re_reg(var0, reg0, 1);
        re_reg(var1, reg1, 0);
        return;
    }
    char op = token[0];
    token = next_token(NULL);
    char *var2 = token;
    int reg0 = reg(var0);
    int reg1 = reg(var1);
    int reg2 = reg(var2);
    switch (op) { // todo
    case '+': break;
    case '-': break;
    case '*': break;
    case '/': break;
    default: break;
    }
    re_reg(var0, reg0, 1);
    re_reg(var1, reg1, 0);
    re_reg(var2, reg2, 0);
}

int reg(char *name) {
    int new_reg = reg_counter++;
    if (name[0] == '*') {        // todo
    } else if (name[0] == '&') { // todo
    } else if (name[0] == '#') { // todo
    } else {                     // todo
    }
}

void re_reg(char *name, int reg, int need_write_back) {
    reg_counter--;
    if (!need_write_back) return;
    if (name[0] == '*' || name[0] == '&' || name[0] == '#') return;
    // todo
}

ir_list_node *generate_funcall(ir_list_node *code) {
    int argCnt = 0;
    // 统计参数数量
    ir_list_node *cur_code = code;
    while (cur_code != NULL) {
        char *line_str = strdup(cur_code->line);
        char *token = next_token(line_str);
        if (strcmp(token, "ARG") != 0) break;
        cur_code = cur_code->next;
        argCnt++;
    }
    // 倒序插入
    ir_list_node *cur_code = code;
    while (cur_code != NULL) {
        char *line_str = strdup(cur_code->line);
        char *token = next_token(line_str);
        if (strcmp(token, "ARG") != 0) break;
        token = next_token(NULL);
        int var_arg = reg(token);
        // todo: $arg -> cnt*4($sp)
        re_reg(token, var_arg, 0);
        cur_code = cur_code->next;
        argCnt--;
    }
    char *line_str = strdup(cur_code->line);
    char *token = next_token(line_str);
    char *val0 = token;
    token = next_token(NULL);
    token = next_token(NULL);
    token = next_token(NULL);
    char *fun_name = token;
    // todo: jal fun
    int reg0 = reg(val0);
    // todo: $v0 -> $reg0;
    re_reg(val0, reg0, 1);
}