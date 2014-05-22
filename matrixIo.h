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
    ifstream internal_storageFile;
    internal_storageFile.open(filename);
    string c;
    int xSize = 0;
    int ySize = 0;
    char* word;
    char* line;
    getline(internal_storageFile, c);
    strcpy(line, c.c_str());
    word = strtok(line, " ");
    while(word != NULL)
    {
      word = strtok(NULL, " ");
      xSize++;
    }
    internal_storageFile.close();
    internal_storageFile.open(filename);

    while(!internal_storageFile.eof())
    {
      getline(internal_storageFile, c);
      ySize++;
    }
    ySize--;
    internal_storage = new double[xSize*ySize];
    internal_storageFile.close();
    internal_storageFile.open(filename);
    int temp;
    for(y = 0; y < ySize; y++)
    {
      for(x = 0; x < xSize; x++)
      {
         internal_storageFile >> internal_storage[xSize * y + x];
      }
    }
    internal_storageFile.close();
    xDim = xSize;
    yDim = ySize;
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
