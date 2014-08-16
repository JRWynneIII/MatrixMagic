#include <iostream>
#include "../matrixMagic.h"
using namespace std;

#define c(r, d) (c[(r)*3 + (d)])
int main(void)
{
  Matrix A;
  Matrix B;
  Matrix c;
  A.readMatrix("matrix.txt");
  B.readMatrix("matrix.txt");
  cout << "Subtracting A and B and returning a pointer\n";
  c = mSub(A,B);
  c.printMatrix();
  cout << "\nB is untouched\n";
  B.printMatrix();
  cout << "Subtracting A and B and overwriting B\n";
  mSub(A,B,1);
  B.printMatrix();
}
