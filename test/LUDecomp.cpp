#include <iostream>
#include "../matrixMagic.h"

using namespace std;

int main(void)
{
  Matrix A;
  Matrix U;
  Matrix L;
  Matrix L2, P;
  cout << "LU Decomposition Test\n";
  A.readMatrix("matrix.txt");
  cout << "Matrix A:\n";
  A.printMatrix();
  A.LUDecomp(L,U);
  cout << "Matrix L:\n";
  L.printMatrix();
  cout << "Matrix U:\n";
  U.printMatrix();
  cout << "Matrix A after decomp: \n";
  A.printMatrix();
  cout << "\nNOTE: Performing LUDecomp will change values inside of A\n";
  mMult(L,U);
  cout << "L*U\n";
  U.printMatrix();
}
