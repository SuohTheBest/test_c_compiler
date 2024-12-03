cmake_minimum_required(VERSION 3.10)
project(compiler)
link_libraries(fl)
add_executable(compiler syntax.tab.c main.c semantic.c semantic.h syntax.h syntax.c yystype.h
        translate.c translate.h)