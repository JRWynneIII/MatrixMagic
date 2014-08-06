#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  Matrix B;
  double* aData = new double[4];
  double* bData = new double[4];
  for (int i = 0; i < 4; i++)
    aData[i] = i+1;
  for (int i = 0; i < 4; i++)
    bData[i] = i+4;
  A.setMatrix(aData,2,2);
  B.setMatrix(bData,2,2);
  std::cout << "mxn Matrix multiplied by mxn Matrix\n";
  multiply(A,B);
  B.printMatrix();
  return 0;
}
