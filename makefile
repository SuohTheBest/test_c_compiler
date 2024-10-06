all: step1 step2 step3

step1:
	flex lexical.l

step2: step1
	gcc lex.yy.c -lfl -o scanner

step3: step2
	./scanner test
