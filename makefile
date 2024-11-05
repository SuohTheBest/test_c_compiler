all: clean parsing
debug: clean parsing_d

parsing:
	bison -d -v syntax.y
	lex lexical.l
	gcc syntax.tab.c main.c syntax.c -lfl -o scanner
	./scanner ./TestCases/Smoke.cmm
parsing_d:
	bison -d -v -t syntax.y
	lex lexical.l
	gcc syntax.tab.c main.c syntax.c -lfl -DDEBUG -o scanner
	./scanner ./TestCases/Smoke.cmm 2> ./debug_log

pack: all
	rm -rf ./Code
	mkdir Code
	cp syntax.tab.c syntax.tab.h syntax.y yystype.h main.c lexical.l lex.yy.c ./Code
	zip -r compiler.zip ./Code ./Reports/report.pdf
	rm -rf ./Code

clean:
	rm -rf lex.yy.c syntax.tab.h syntax.tab.c syntax.output debug_log scanner