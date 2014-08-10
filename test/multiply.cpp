#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  Matrix B;
  double* result;
  double vec[3] = {15,31,661};

  A.readMatrix("matrix.txt");
  B.setMatrix(vec,1,3);

  std::cout << "nxn Matrix multiplied by 1xn Vector returning a pointer\n";
  result = mMult(A,B,2);

  for (int i = 0; i<3; i++)
    std::cout << result[i] << std::endl;

  std::cout << "\nB is untouched vector\n";
  B.printMatrix();

  std::cout << "\n\nnxn Matrix multiplied by 1xn Vector overwriting B\n";
  mMult(A,B);
  B.printMatrix();

  return 0;
}
