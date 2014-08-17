#include <iostream>
#include "../matrixMagic.h"
using namespace std;

int main(void)
{
  Matrix A;
  A.readMatrix("matrix.txt");
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      cout << A(i,j) << " ";
    }
    cout << endl;
  }
}
