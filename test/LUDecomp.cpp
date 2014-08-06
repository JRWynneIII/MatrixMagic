#include <iostream>
#include "../matrixMagic.h"

using namespace std;

int main(void)
{
  Matrix A;
  cout << "LU Decomposition Test\n";
  A.readMatrix("matrix.txt");
  A.LUDecomp();
}
