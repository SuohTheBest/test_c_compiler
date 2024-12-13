#include "generator.h"
#include "semantic.h"
#include "syntax.h"
#include "translate.h"

int main(int argc, char **argv) {
#ifdef P_DEBUG
    yydebug = 1;
#endif
    assert(argc > 2);
    int err_flag;
    err_flag = syntax_analysis(argv[1]);
    if (err_flag) return 0;
    err_flag = semantic_analysis(tree_root);
    if (err_flag) return 0;
    int ir_output = argc > 3 ? 1 : 0;
#ifdef _DEBUG
    ir_output = 1;
#endif
    err_flag = translate_code(argc > 3 ? argv[3] : argv[2], tree_root, ir_output);
    if (err_flag) return 0;
    generate_mips(midCode, argv[2]);
    return 0;
}