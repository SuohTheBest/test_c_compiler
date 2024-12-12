c_src := generator.c translate.c semantic.c syntax.tab.c syntax.c main.c
other_src := generator.h translate.h semantic.h syntax.tab.h syntax.h syntax.y yystype.h lexical.l
target := ./MakeOut/compiler
CC := gcc -lfl -o $(target)

all: clean cc_compile run
vs_debug: clean cc_compile_d

clean:
	rm -rf ./MakeOut

parsing:
	bison -d syntax.y
	lex lexical.l

cc_compile: parsing
	$(CC) $(c_src)

cc_compile_d: parsing
	$(CC) $(c_src) -g

run:
	$(target) ./TestCases/Smoke.cmm ./MakeOut/output.s

pack:
	rm -f ./MakeOut/compiler.zip
	find ./Code -type f ! -iname "makefile" -exec rm -f {} +
	cp $(c_src) $(other_src) ./Code
	zip -r ./MakeOut/compiler.zip ./Code ./Reports/report.pdf

parsing_d:
	bison -d -v -t syntax.y
	lex lexical.l
	$(CC) $(c_src) -DP_DEBUG
	$(target) ./TestCases/Smoke.cmm 2> ./MakeOut/debug_log

test: all
	cd ./nju-compiler-test/lab2 && python3 ./test.py -p ../../scanner -g 1