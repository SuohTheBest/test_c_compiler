#include "semantic.h"
#include "syntax.h"
#include "translate.h"

int main(int argc, char **argv) {
#ifdef DEBUG
    yydebug = 1;
#endif
    assert(argc > 2);
    int err_flag;
    err_flag = syntax_analysis(argv[1]);
    if (err_flag) return 0;
    err_flag = semantic_analysis(tree_root);
    if (err_flag) return 0;
    err_flag = translate_code(argv[2], tree_root);
    if (err_flag) return 0;
    return 0;
}