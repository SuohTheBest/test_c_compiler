#include "syntax.h"
#include "semantic.h"

int main(int argc, char **argv) {
#ifdef DEBUG
    yydebug = 1;
#endif
    syntax_analysis(argc, argv);
    if (error_flag) return 0;
    semantic_analysis(tree_root);
    return 0;
}