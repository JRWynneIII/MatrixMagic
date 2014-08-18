CC=g++
CFLAGS=-L ./lib
CPPFLAGS= -g -lMatrixMagic
FILENAME:=  $(patsubst %.cpp,%,$(wildcard test/*.cpp))

all : matrixMagic.cpp lib
	$(CC) -g -fpic -c matrixMagic.cpp -o matrixMagic.o
	$(CC) -shared -o lib/libMatrixMagic.so matrixMagic.o

tests : $(FILENAME)

% : %.cpp
	$(CC) $(CFLAGS) $< -o $@.test $(CPPFLAGS)

clean:
	rm -f *.o
	rm -f test/*.test
