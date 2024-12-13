cmake_minimum_required(VERSION 3.10)
project(compiler)
link_libraries(fl)
add_executable(compiler syntax.tab.c main.c semantic.c semantic.h syntax.h syntax.c yystype.h
        translate.c translate.h generator.c)
#target_compile_definitions(compiler PRIVATE -D_DEBUG)
add_executable(test_c ./TestCases/test.c)