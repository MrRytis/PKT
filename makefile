clc:
	flex cmm.l
	bison cmm.y
	gcc l.c p.c cmm.c main.c -o compiler
	./compiler codeFib.cl

clean :
	del l.h l.c p.h p.c compiler
