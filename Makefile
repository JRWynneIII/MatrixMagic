CC=g++
CFLAGS=-L ./lib
CPPFLAGS= -std=c++11 -g -lMatrixMagic
FILENAME:=  $(patsubst %.cpp,%,$(wildcard test/*.cpp))

all : matrixMagic.cpp lib
	$(CC) -std=c++11 -g -fpic -c matrixMagic.cpp -o matrixMagic.o
	$(CC) -std=c++11 -shared -o lib/libMatrixMagic.so matrixMagic.o

tests : $(FILENAME)

% : %.cpp
	$(CC) $(CFLAGS) $< -o $@.test $(CPPFLAGS)

clean:
	rm -f *.o
	rm -f test/*.test
