#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  Matrix B;
  A.readMatrix("matrix.txt");
  B.readMatrix("matrix.txt");
  std::cout << "nxn Matrix multiplied by nxn Matrix\nThis test should fail.\n";
  multiply(A,B);  //Result will be in B
  B.printMatrix();
  return 0;
}
