#ifndef MATRIXIO_H
#define MATRIXIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

template<typename T>
class Matrix
{

public:
  Matrix()
  {
    matrix=NULL;
  }

  ~Matrix()
  {
    delete[] matrix;
  }
  void readMatrix(char* filename, int xDim, int yDim)
  {
    int x = 0;
    int y = 0;
    matrix = new T[xDim*yDim];
    ifstream matrixFile;
    matrixFile.open(filename);
    while(!matrixFile.eof())
    {
      matrixFile >> matrix[xDim * y + x];
      if (x == xDim)
        y++;
      x++;
    }
  }

  void printMatrix(int xDim, int yDim)
  {
    for (int y = 0; y < yDim; y++)
    {
      for (int x = 0; x < xDim; x++)
        cout << matrix[xDim * y + x];
      cout << endl;
    }
  }
private:
  T* matrix;
};
#endif
