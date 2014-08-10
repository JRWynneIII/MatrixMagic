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
  cout << "Adding A and B and returning a pointer\n";
  c = mAdd(A,B,0);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      cout << c(i,j) << " ";
    cout << endl;
  }
  cout << "\nB is untouched\n";
  B.printMatrix();
  cout << "Adding A and B and overwriting B\n";
  mAdd(A,B);
  B.printMatrix();
}
