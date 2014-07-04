#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  Matrix B;
  double vec[3] = {1,1,1};
  B.setMatrix(vec,1,3);
  A.readMatrix("matrix.txt");
  std::cout << "Matrix A\n";
  A.printMatrix();
  std::cout << "Matrix B\n";
  B.printMatrix();
  std::cout << "Assigning B to A\n";
  A = B;
  A.printMatrix();
  return 0;
}
