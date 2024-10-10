all: clean step1 step2 step3 step4

step1:
	bison -d -v syntax.y

step2:
	flex lexical.l

step3:
	gcc syntax.tab.c main.c -lfl -o scanner

step4:
	./scanner test

clean:
	rm -rf lex.yy.c syntax.tab.h syntax.tab.c syntax.output scanner
