#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A, B;
  double b = 5;
  A.readMatrix("matrix.txt");
  B = A * b;
  std::cout << "Matrix times a scalar\n";
  B.print();
  A.empty();
  B.empty();
  std::cout << "Vector times a scalar\n";
  A.read("vector.txt");
  A.print();
  std::cout << std::endl;
  B = A * b;
  B.print();
  return 0;
}
