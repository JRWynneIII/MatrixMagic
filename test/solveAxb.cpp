#include <iostream>
#include "../matrixMagic.h"
using namespace std;

int main(void)
{
  Matrix A,b;
  A.readMatrix("matrix2.txt");
  b.readMatrix("vector.txt");
  solveAxb(A,b).print();
}
