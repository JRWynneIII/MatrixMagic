#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  Matrix B;
  Matrix result;
  double* vec = new double[3];
  vec[0] = 15;
  vec[1] = 31;
  vec[2] = 661;

  A.readMatrix("matrix.txt");
  B.setMatrix(vec,1,3);

  std::cout << "nxn Matrix multiplied by 1xn Vector returning a matrix\n";
  result = mMult(A,B);

  result.printMatrix();

  std::cout << "\nB is untouched vector\n";
  B.printMatrix();

  std::cout << "\n\nnxn Matrix multiplied by 1xn Vector overwriting B\n";
  mMult(A,B,1);
  B.printMatrix();

  return 0;
}
