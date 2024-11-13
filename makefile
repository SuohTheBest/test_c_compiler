all: clean parsing
debug: clean parsing_d

parsing:
	bison -d -v syntax.y
	lex lexical.l
	gcc semantic.c syntax.tab.c main.c syntax.c -lfl -o scanner
	./scanner ./TestCases/Smoke.cmm

parsing_d:
	bison -d -v -t syntax.y
	lex lexical.l
	gcc semantic.c syntax.tab.c main.c syntax.c -lfl -DDEBUG -o scanner
	./scanner ./TestCases/Smoke.cmm 2> ./debug_log

pack:
	rm compiler.zip
	find ./Code -type f ! -iname "makefile" -exec rm -f {} +
	cp syntax.c syntax.h semantic.c semantic.h syntax.tab.c syntax.tab.h syntax.y yystype.h main.c lexical.l lex.yy.c ./Code
	zip -r compiler.zip ./Code ./report.pdf
	cd ./Code
	make

test: all
	cd ./nju-compiler-test/lab2 && python3 ./test.py -p ../../scanner -g 1

clean:
	rm -rf lex.yy.c syntax.tab.h syntax.tab.c syntax.output debug_log scanner