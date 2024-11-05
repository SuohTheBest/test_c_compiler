#include "semantic.h"

type_node sem_type_map[1024];
type_node sem_name_map[1024];


unsigned hash_pjw(char *name) {
    unsigned val = 0, i;
    for (; *name; ++name) {
        val = (val << 2) + *name;
        if ((i = val & ~0x3fff)) val = (val ^ (i >> 12)) & 0x3fff;
    }
    return val;
}