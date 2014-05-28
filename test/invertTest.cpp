#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  A.readMatrix("matrix.txt");
  std::cout << "Original Matrix\n";
  A.printMatrix();
  std::cout << "Inverted Matrix\n";
  A.invert();
  A.printMatrix();
  std::cout << "Re-inverted to get original matrix\n";
  A.invert();
  A.printMatrix();
  Matrix B;
  B.readMatrix("vector.txt");
  std::cout << std::endl << "Original Vector\n";
  B.printMatrix();
  std::cout << "Inverted Vector\n";
  B.invert();
  B.printMatrix();
  std::cout << "Re-inverted to get original Vector\n";
  B.invert();
  B.printMatrix();
  return 0;
}
