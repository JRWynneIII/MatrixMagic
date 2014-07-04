#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  Matrix B;
  Matrix C;
  double vec[3] = {1,1,1};
  A.readMatrix("matrix.txt");
  B.setMatrix(vec,1,3);
  std::cout << "nxn Matrix multiplied by 1xn Vector\n";
  C = (A * B);
  C.printMatrix();
  return 0;
}
