#include <iostream>
#include "../matrixMagic.h"
using namespace std;

int main(void)
{
  Matrix A;
  Matrix B;
  Matrix C;
  A.readMatrix("matrix.txt");
  B.readMatrix("matrix.txt");
  cout << "Product of A and B using mMult()\n";
  C = mMult(A,B);
  C.printMatrix();
  C.empty();
  cout << "Product of A and B using Overloaded operator *\n";
  C = A * B;
  C.printMatrix();
}
