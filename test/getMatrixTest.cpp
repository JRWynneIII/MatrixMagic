#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix matrixA;
  double* a;
  std::cout << "Reading in matrix\n";
  matrixA.readMatrix("matrix.txt");
  std::cout << "Printing out matrix from object\n";
  matrixA.printMatrix();
  std::cout << "Retrieving Array from object\n";
  a = matrixA.getMatrix();
  std::cout << std::endl;
  std::cout << "Listing out retrieved array\n";
  for(int i = 0; i<(matrixA.getX()*matrixA.getY()); i++)
    std::cout << a[i] << std::endl;
  return 0;
}
