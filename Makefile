CC=g++
CFLAGS=-L ./lib
CPPFLAGS=-lMatrixMagic
FILENAME:=  $(patsubst %.cpp,%,$(wildcard test/*.cpp))

all: matrixMagic.cpp lib
	g++ -fpic -c matrixMagic.cpp -o matrixMagic.o
	g++ -shared -o lib/libMatrixMagic.so matrixMagic.o

tests: $(FILENAME)

% : %.cpp
	    g++ $(CFLAGS) $< -o $@ $(CPPFLAGS)
