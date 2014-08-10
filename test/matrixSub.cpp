#include <iostream>
#include "../matrixMagic.h"
using namespace std;

#define c(r, d) (c[(r)*3 + (d)])
int main(void)
{
  Matrix A;
  Matrix B;
  double* c;
  A.readMatrix("matrix.txt");
  B.readMatrix("matrix.txt");
  cout << "Subtracting A and B and returning a pointer\n";
  c = mSub(A,B,0);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      cout << c(i,j) << " ";
    cout << endl;
  }
  cout << "\nB is untouched\n";
  B.printMatrix();
  cout << "Subtracting A and B and overwriting B\n";
  mSub(A,B);
  B.printMatrix();
}
