c_src := generator.c translate.c semantic.c syntax.tab.c syntax.c main.c
other_src := generator.h translate.h semantic.h syntax.tab.h syntax.h syntax.y yystype.h lexical.l
target := ./MakeOut/compiler
CC := gcc -lfl -o $(target)

all: clean cc_compile run
debug: clean cc_compile_d run
vs_debug: clean cc_compile_d

clean:
	rm -rf ./MakeOut

parsing:
	if [ ! -d "MakeOut" ]; then \
        mkdir MakeOut; \
    fi
	bison -d syntax.y
	lex lexical.l

cc_compile: parsing
	$(CC) $(c_src)

cc_compile_d: parsing
	$(CC) $(c_src) -g -D_DEBUG

run:
	$(target) ./TestCases/Smoke.c ./MakeOut/output.s > ./MakeOut/compiler_stdout.txt

pack:
	rm -rf ./MakeOut/compiler.zip ./Code
	mkdir Code
	cp $(c_src) $(other_src) ./Code
	cp ./Reports/report.pdf ./
	zip -r ./MakeOut/compiler.zip ./Code ./report.pdf
	rm -rf ./report.pdf ./Code

parsing_d:
	bison -d -v -t syntax.y
	lex lexical.l
	$(CC) $(c_src) -DP_DEBUG
	$(target) ./TestCases/Smoke.cmm 2> ./MakeOut/debug_log

test: all
	cd ./nju-compiler-test/lab4 && ./run.sh -r ../../MakeOut/compiler -e base -l 4