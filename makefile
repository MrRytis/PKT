clc:
	flex cancer_lang.l
	bison cancer_lang.y
	gcc lexer.c parser.c cancer_lang.c main.c -o cancer_lang
	./cancer_lang code.cl

clean :
	del lexer.h lexer.c parser.h parser.c cancer_lang.exe
