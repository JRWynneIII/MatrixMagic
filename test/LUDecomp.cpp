#include <iostream>
#include "../matrixMagic.h"

using namespace std;

int main(void)
{
  Matrix A;
  Matrix U;
  Matrix L;
  cout << "LU Decomposition Test\n";
  A.readMatrix("matrix.txt");
  cout << "Matrix A:\n";
  A.printMatrix();
  A.LUDecomp(L,U);
  cout << "Matrix L:\n";
  L.printMatrix();
  cout << "Matrix U:\n";
  U.printMatrix();
  cout << "\nNOTE: Performing LUDecomp will change values inside of A\n";
}
