#include <iostream>
#include "../matrixMagic.h"
using namespace std;

int main(void)
{
  Matrix A,b;
  A.readMatrix("A.txt");
  b.readMatrix("b.txt");
  solveAxb(A,b).print();
}
