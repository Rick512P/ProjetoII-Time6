index:
	clear
	gcc -o executavel Arquivos-c/*.c
#clear
	./executavel

testes:
	clear
	gcc -o Testes -g Arquivos-c/*.c
	gdb ./Testes

clear:
	@if [ -f executavel ]; then \
		rm executavel; \
	fi
	@if [ -f executavel.exe ]; then \
		rm executavel.exe; \
	fi
	clear

ccleartestes:
	@if [ -f Testes ]; then \
		rm Testes; \
	fi
	clear