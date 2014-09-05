CC=nvcc
CFLAGS=-L ./lib
CPPFLAGS= -arch=sm_35 -g -lMatrixMagic
FILENAME:=  $(patsubst %.cpp,%,$(wildcard test/*.cpp))

all : matrixMagic.cpp lib
	$(CC) -arch=sm_35 --shared -g --compiler-options '-fPIC' -c matrixMagic.cpp -o matrixMagic.o
	$(CC) -arch=sm_35 --shared -g --compiler-options '-fPIC' -c matrixMagic.cu -o cudaMatrixMagic.o
	$(CC) -arch=sm_35 --shared -o lib/libMatrixMagic.so matrixMagic.o cudaMatrixMagic.o
	cp lib/libMatrixMagic.so $(MEMBERWORK)/stf007

tests : $(FILENAME)

% : %.cpp
	$(CC) $(CFLAGS) $< -o $@.test $(CPPFLAGS)

clean:
	rm -f *.o
	rm -f test/*.test
