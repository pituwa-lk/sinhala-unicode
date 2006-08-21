all: sintex 

sintex: lex.yy.c
	gcc -o sintex lex.yy.c -lfl

lex.yy.c: sintex.lex
	flex sintex.lex

	
