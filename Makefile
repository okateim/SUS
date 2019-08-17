all: main kmis SUS SS slide

clean:
	rm -f *.o main kmis SUS SS slide

main: divsufsort.c main.cpp
	gcc -Wall -o divsufsort.o -c divsufsort.c
	g++ -Wall -o main.o -c -I./lib main.cpp
	g++ -Wall -o main divsufsort.o main.o

kmis: divsufsort.c kmis.cpp
	gcc -Wall -o divsufsort.o -c divsufsort.c
	g++ -Wall -o kmis.o -c -I./lib kmis.cpp
	g++ -Wall -o kmis divsufsort.o kmis.o

SUS: divsufsort.c SUS.cpp
	gcc -Wall -o divsufsort.o -c divsufsort.c
	g++ -Wall -o SUS.o -c -I./lib SUS.cpp
	g++ -Wall -o SUS divsufsort.o SUS.o

SS: divsufsort.c SS.cpp
	gcc -Wall -o divsufsort.o -c divsufsort.c
	g++ -Wall -o SS.o -c -I./lib SS.cpp
	g++ -Wall -o SS divsufsort.o SS.o

slide: divsufsort.c slide.cpp
	gcc -Wall -o divsufsort.o -c divsufsort.c
	g++ -Wall -o slide.o -c -I./lib slide.cpp -std=c++11
	g++ -Wall -o slide divsufsort.o slide.o
