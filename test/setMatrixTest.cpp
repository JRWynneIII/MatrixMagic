#include <iostream>
#include "../matrixIo.h"

int main(void)
{
  Matrix matrixA;
  double* a = new double[9];
  for (int i=0; i<9; i++)
    a[i] = i+1;
  matrixA.setMatrix(a,3,3);
  matrixA.printMatrix();
  return 0;
}
