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
    matrix=NULL;
    xDim = yDim = 0;
  }

  ~Matrix()
  {
    delete[] matrix;
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
    char* line;
    getline(matrixFile, c);
    strcpy(line, c.c_str());
    word = strtok(line, " ");
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
    matrix = new double[xSize*ySize];
    matrixFile.close();
    matrixFile.open(filename);
    int temp;
    for(y = 0; y < ySize; y++)
    {
      for(x = 0; x < xSize; x++)
      {
         matrixFile >> matrix[xSize * y + x];
      }
    }
    matrixFile.close();
    xDim = xSize;
    yDim = ySize;
  }

  void printMatrix()
  {
    for (int y = 0; y < yDim; y++)
    {
      for (int x = 0; x < xDim; x++)
        cout << fixed << matrix[xDim * y + x] << " ";
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
