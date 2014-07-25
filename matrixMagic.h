#ifndef MATRIXMAGIC_H
#define MATRIXMAGIC_H
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
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
    //delete[] internal_storage;
  }

//  Matrix operator*(Matrix &rh)
//  {
//    //TODO:Matrix!Matrix multiply and Matrix!scalar multiply
//  }
//
//  Matrix& operator= (Matrix &rhs)
//  {
//    if (this != &rhs)
//    {
//      this->setMatrix(rhs.getMatrix(),rhs.getX(),rhs.getY());
//      rhs.empty();
//      return *this;
//    }
//  }

  void transpose()
  {
    if (yDim !=  1 && xDim != 1)
    {
      for (int i=0; i < yDim; i++) //y
        for (int j=i+1; j < xDim; j++) //x
        {
          int temp = internal_storage[i * xDim + j];
          internal_storage[i * xDim + j] = internal_storage[j * xDim + i];
          internal_storage[j * xDim + i] = temp;
        }
    }
    int tmp = xDim;
    xDim = yDim;
    yDim = tmp;
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
    internal_storage = NULL;
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

  bool isVector()
  {
    if (this->getX() == 1 || this->getY() == 1)
      return true;
    else
      return false;
  }

  void empty()
  {
    delete[] internal_storage;
  }


private:
  double* internal_storage;
  int xDim;
  int yDim;
};

Matrix multiply(Matrix& A, Matrix& B)
{
  int n;
  if (A.isVector())
  {
    n = B.getX();
  }

  else
  {
    n = A.getX();
  }

  //do dot product
  double* a_raw = A.getMatrix();
  double* b_raw = B.getMatrix();
  double* resultant = (double*)malloc(n*sizeof(double));
  double res = 0.0;
  int i;
  for (int j = 0; j < n; j++)
  {
    for (i = 0; i < n; i++)
    {
        res += a_raw[i] * b_raw[i];
    }
    resultant[i] = res;
  }

  B.setMatrix(resultant,1,n);

  return B;
}
#endif
