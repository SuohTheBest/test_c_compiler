#include "syntax.h"
#include "semantic.h"

int main(int argc, char **argv) {
#ifdef DEBUG
    yydebug = 1;
#endif
    syntax_analysis(argc, argv);
    sem_read_tree(tree_root);
    return 0;
}