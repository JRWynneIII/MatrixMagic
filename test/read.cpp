#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A, B;
  A.readMatrix("matrix.txt");
  A.printMatrix();
  A.empty();
  A.read("matrix.txt");
  std::cout << std::endl;
  A.printMatrix();
  std::cout << "X: " << A.getX() << "\tY: " << A.getY() << std::endl;
  B.read("vector.txt");
  B.print();
  std::cout << "X: " << B.getX() << "\tY: " << B.getY() << std::endl;
  return 0;
}
