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
  C = A + B;
  C.printMatrix();
}
