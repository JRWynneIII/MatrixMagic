#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  A.readMatrix("matrix.txt");
  std::cout << "Original Matrix\n";
  A.printMatrix();
  std::cout << "Transposed Matrix\n";
  A.transpose();
  A.printMatrix();
  std::cout << "Re-transposed to get original matrix\n";
  A.transpose();
  A.printMatrix();
  Matrix B;
  B.readMatrix("vector.txt");
  std::cout << std::endl << "Original Vector\n";
  B.printMatrix();
  std::cout << "Transposed Vector\n";
  B.transpose();
  B.printMatrix();
  std::cout << "Re-transposed to get original Vector\n";
  B.transpose();
  B.printMatrix();
  return 0;
}
