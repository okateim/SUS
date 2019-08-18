all: main kmis SUS intervalSUS SS slide

clean:
	rm -f *.o main kmis SUS SS slide

main: lib/divsufsort.c main.cpp
	gcc -Wall -o ./divsufsort.o -c ./lib/divsufsort.c
	g++ -Wall -o main.o -c -I./lib main.cpp
	g++ -Wall -o main divsufsort.o main.o

kmis: lib/divsufsort.c kmis.cpp
	gcc -Wall -o ./divsufsort.o -c ./lib/divsufsort.c
	g++ -Wall -o kmis.o -c -I./lib kmis.cpp
	g++ -Wall -o kmis divsufsort.o kmis.o

SUS: lib/divsufsort.c SUS.cpp
	gcc -Wall -o ./divsufsort.o -c ./lib/divsufsort.c
	g++ -Wall -o SUS.o -c -I./lib SUS.cpp
	g++ -Wall -o SUS divsufsort.o SUS.o

intervalSUS: lib/divsufsort.c lib/rmq.c intervalSUS.cpp
	gcc -Wall -o ./divsufsort.o -c ./lib/divsufsort.c
	gcc -Wall -o ./rmq.o -c ./lib/rmq.c
	g++ -Wall -o intervalSUS.o -c -I./lib -DUSERMQ intervalSUS.cpp
	g++ -Wall -o intervalSUS divsufsort.o rmq.o intervalSUS.o

SS: lib/divsufsort.c SS.cpp
	gcc -Wall -o ./divsufsort.o -c ./lib/divsufsort.c
	g++ -Wall -o SS.o -c -I./lib SS.cpp
	g++ -Wall -o SS divsufsort.o SS.o

slide: lib/divsufsort.c slide.cpp
	gcc -Wall -o ./divsufsort.o -c ./lib/divsufsort.c
	g++ -Wall -o slide.o -c -I./lib slide.cpp -std=c++11
	g++ -Wall -o slide divsufsort.o slide.o
