all: clean step1 step2 step3 step4
debug: clean step1_d step2 step3_d step4_d

step1:
	bison -d -v syntax.y

step1_d:
	bison -d -v -t syntax.y

step2:
	flex lexical.l

step3:
	gcc syntax.tab.c main.c -lfl -o scanner

step3_d:
	gcc syntax.tab.c main.c -lfl -DDEBUG -o scanner

step4:
	./scanner test

step4_d:
	./scanner test 2> ./debug_log

pack: all
	rm -f ./Code/*.c ./Code/*.h ./Code/*.l ./Code/*.y ./Code/*.o
	cp syntax.tab.c syntax.tab.h syntax.y yystype.h main.c lexical.l lex.yy.c ./Code
	zip -r compiler.zip ./Code report.pdf

clean:
	rm -rf lex.yy.c syntax.tab.h syntax.tab.c syntax.output debug_log scanner
