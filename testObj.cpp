#include <iostream>
#include "matrixIo.h"

int main(void)
{
  Matrix<int> matrixA;
  matrixA.readMatrix("matrix.txt", 3, 3);
  matrixA.printMatrix(3,3);
  return 0;
}
