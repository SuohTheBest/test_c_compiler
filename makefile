all: clean compile run
vs_debug: clean compile_d

compile:
	bison -d -v syntax.y
	lex lexical.l
	gcc translate.c semantic.c syntax.tab.c main.c syntax.c -lfl -o scanner

compile_d:
	bison -d -v syntax.y
	lex lexical.l
	gcc translate.c semantic.c syntax.tab.c main.c syntax.c -lfl -g -o scanner

run:
	./scanner ./TestCases/Smoke.cmm ./ts.output

parsing_d:
	bison -d -v -t syntax.y
	lex lexical.l
	gcc syntax.tab.c main.c syntax.c -lfl -DDEBUG -o scanner
	./scanner ./TestCases/Smoke.cmm 2> ./debug_log

pack:
	rm -f compiler.zip
	find ./Code -type f ! -iname "makefile" -exec rm -f {} +
	cp translate.c translate.h syntax.c syntax.h semantic.c semantic.h syntax.tab.c syntax.tab.h syntax.y yystype.h main.c lexical.l lex.yy.c ./Code
	zip -r compiler.zip ./Code ./report.pdf
	cd ./Code
	make

test: all
	cd ./nju-compiler-test/lab2 && python3 ./test.py -p ../../scanner -g 1

clean:
	rm -rf syntax.output debug_log scanner ts_out.ir