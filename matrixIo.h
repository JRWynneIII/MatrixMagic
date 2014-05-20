#ifndef MATRIXIO_H
#define MATRIXIO_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Matrix
{

public:
  Matrix()
  {
    matrix=NULL;
    xDim = yDim = 0;
  }

  ~Matrix()
  {
    delete[] matrix;
  }
  void readMatrix(const char* filename, int xSize, int ySize)
  {
    int x = 0;
    int y = 0;
    matrix = new double[xSize*ySize];
    ifstream matrixFile;
    matrixFile.open(filename);
    for(x = 0; x < xSize; x++)
    {
      for(y = 0; y < ySize; y++)
      {
        matrixFile >> matrix[xSize * y + x];
      }
    }
    xDim = xSize;
    yDim = ySize;
  }

  void printMatrix()
  {
    for (int y = 0; y < yDim; y++)
    {
      for (int x = 0; x < xDim; x++)
        cout << matrix[xDim * y + x] << " ";
      cout << endl;
    }
  }

  int getX()
  {
    return xDim;
  }
  
  int getY()
  {
    return yDim;
  }

private:
  double* matrix;
  int xDim;
  int yDim;
};
#endif
