#include <iostream>
#include "matrixIo.h"

int main(void)
{
  Matrix matrixA;
  matrixA.readMatrix("s3dkt3m2.dat",8,11306);
  matrixA.printMatrix();
  return 0;
}
