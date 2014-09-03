#include <iostream>
#include "../matrixMagic.h"
using namespace std;

int main(void)
{
  Matrix A, B, C;
  A.readMatrix("vector.txt");
  B.readMatrix("vector.txt");
  cout << "Original A:\n";
  A.print();
  cout << "Original B:\n";
  B.print();
  C = A.transpose()*A;
  cout << "C:\n";
  C.print();
  cout << "A:\n";
  A.print();
  cout << "B:\n";
  B.print();
  return 0;
}
