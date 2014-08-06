#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix matrixA;
  matrixA.readMatrix("matrix.txt");
  matrixA.printMatrix();
  return 0;
}
