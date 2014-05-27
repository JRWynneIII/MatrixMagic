#ifndef MATRIXIO_H
#define MATRIXIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <string>
#include <cstdlib>
using namespace std;

class Matrix
{
public:
  Matrix()
  {
    internal_storage=NULL;
    xDim = yDim = 0;
  }

  ~Matrix()
  {
    delete[] internal_storage;
  }
  void readMatrix(const char* filename)
  {
    int x = 0;
    int y = 0;
    ifstream matrixFile;
    matrixFile.open(filename);
    string c;
    int xSize = 0;
    int ySize = 0;
    char* word;
    getline(matrixFile, c);
    word = strtok((char*)c.c_str(), " ");
    while(word != NULL)
    {
      word = strtok(NULL, " ");
      xSize++;
    }
    matrixFile.close();
    matrixFile.open(filename);

    while(!matrixFile.eof())
    {
      getline(matrixFile, c);
      ySize++;
    }
    ySize--;
    internal_storage = new double[xSize*ySize];
    matrixFile.close();
    matrixFile.open(filename);
    int temp;
    for(y = 0; y < ySize; y++)
    {
      for(x = 0; x < xSize; x++)
      {
         matrixFile >> internal_storage[xSize * y + x];
      }
    }
    matrixFile.close();
    xDim = xSize;
    yDim = ySize;
  }

  void setMatrix(double* external, int x, int y)
  {
    internal_storage = external;
    xDim = x;
    yDim = y;
  }

  double* getMatrix()
  {
    return internal_storage;
  }
  void printMatrix()
  {
    for (int y = 0; y < yDim; y++)
    {
      for (int x = 0; x < xDim; x++)
        cout << fixed << internal_storage[xDim * y + x] << " ";
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
  double* internal_storage;
  int xDim;
  int yDim;
};
#endif
