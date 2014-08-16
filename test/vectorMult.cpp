#include <iostream>
#include "../matrixMagic.h"

int main(void)
{
  Matrix A;
  Matrix B;
  double vec[3] = {1,1,1};
  double vec2[3] = {2,3,4};
  A.setMatrix(vec,3,1);
  B.setMatrix(vec2,1,3);
  std::cout << "1xn Vector multiplied by 1xn Vector\n";
  mMult(A,B,1);
  B.printMatrix();
  return 0;
}
