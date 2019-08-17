all: divsufsort main

divsufsort: divsufsort.c
	gcc -o divsufsort.o -c divsufsort.c

main: main.cpp divsufsort.o
	g++ -o main.o -c main.cpp
	g++ divsufsort.o main.o
