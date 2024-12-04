c_src := translate.c semantic.c syntax.tab.c syntax.c main.c
other_src := translate.h semantic.h syntax.tab.h syntax.h syntax.y yystype.h lexical.l
CC := gcc -lfl -o scanner

all: clean cc_compile run
vs_debug: clean cc_compile_d

clean:
	rm -rf compiler.zip syntax.output debug_log scanner ts_out.ir

parsing:
	bison -d syntax.y
	lex lexical.l

cc_compile: parsing
	$(CC) $(c_src)

cc_compile_d: parsing
	$(CC) $(c_src) -g

run:
	./scanner ./TestCases/Smoke.cmm ./ts_out.ir

parsing_d:
	bison -d -v -t syntax.y
	lex lexical.l
	$(CC) $(c_src) -DP_DEBUG
	./scanner ./TestCases/Smoke.cmm 2> ./debug_log

pack:
	rm -f compiler.zip
	find ./Code -type f ! -iname "makefile" -exec rm -f {} +
	cp $(c_src) $(other_src) ./Code
	zip -r compiler.zip ./Code ./report.pdf

test: all
	cd ./nju-compiler-test/lab2 && python3 ./test.py -p ../../scanner -g 1