all: PROJET EXECUTION

fonctions.o : fonctions.c fonctions.h librairies.h
			gcc -c -Wall fonctions.c
main.o : main.c fonctions.h librairies.h
			gcc -c -Wall main.c
PROJET : fonctions.o main.o
			gcc -o PROJET fonctions.o main.o
EXECUTION :
		./PROJET
