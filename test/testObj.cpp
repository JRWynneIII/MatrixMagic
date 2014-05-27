#include <iostream>
#include "matrixIo.h"

int main(void)
{
  Matrix matrixA;
  matrixA.readMatrix("s3dkt3m2.dat");
  matrixA.printMatrix();
  return 0;
}
