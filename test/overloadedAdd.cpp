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
  cout << "A + B using mAdd():\n";
  C = mAdd(A,B);
  C.printMatrix();
  C.empty();
  cout << "A - B using overloaded operator:\n";
  C = A + B;
  C.printMatrix();
}
