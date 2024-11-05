#include "syntax.h"

int main(int argc, char **argv) {
#ifdef DEBUG
    yydebug = 1;
#endif
    syntax_analysis(argc, argv);
    return 0;
}