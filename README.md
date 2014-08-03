MatrixMagic
===========

A scalable, CUDA accelerated set of linear algebra functions

This library is designed to make working with matricies and vectors simpler for the programmer. Simply `#include` the `matrixMagic.h` header file and use `-L ./lib` and `-lMatrixMagic` and they will provide you with access to the `Matrix` class and various other functions.

So far, this provides the user with:
* The `Matrix` object. You use this for both matricies and vectors, just specify which dimension is of size 1 with `.setMatrix`
  - `.transpose()` will transpose your matrix or vector for you
  - `.readMatrix()` provides you with a simple way to read in a matrix from a file into the object
  - `.setMatrix()` allows you to define a 1 or 2 dimensional array ***on the heap*** and pass it and the dimensions into the object
  - `.getMatrix()` will return a pointer to the internal double array. For the sake of simplicity, all 2 dimensional matricies are stored as a 1 dimensional array inside the object.
  - `.getX()` will return the size in the X dimension (i.e. number of columns)
  - `.getY()` will return the size in the Y dimension (i.e. number of rows)
  - `.isVector()` is used to query the object whether the matrix is a vector or not. This will return `true` if it is a vector and `false` if it isn't
  - `.empty()` will delete the internal `double` array
* Also provided is a simple to use `multiply()` function. This can be used to do Matrix * Vector or Vector * Vector operations. Also supported is multiplication of 2 square matrices

And many more functions/features are in the works, including LU decomposition and Conjugate Gradient routines.

As of now, all functions and objects are defined inside the main header file. This will be changed in the future to be more like a typical C++ library.

To recompile the MatrixMagic shared library, simply run:
```
$ make
```

To compile all the tests, run:
```
$ make tests
```

Files
===========
`matrix.txt` -- Small test matrix   
`vector.txt` -- Small test vector 
`matrixMagic.h` -- Contains the Matrix class  
`s3dkt3m2.dat` -- Part of a matrix from the [Matrix Market](http://math.nist.gov/MatrixMarket/index.html)  
`makefile` -- Allows you to make the shared library and to compile all the tests
`test/` -- Directory that contains test code for each of MatrixMagic's features and functions.
