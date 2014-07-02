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
    delete[] internal_storage;
  }

  Matrix* operator*(Matrix &rh)
  {
    //store results in the vector. return a pointer to it
    if ((this->isVector() && !rh.isVector()) || (rh.isVector() && !this->isVector())
    {
      //One of the matricies are vectors
      int m = 0;
      int n = 0;
      bool rhIsVector = true;
      double* resultant;
      double temp = 0;
      double* lh = this->getMatrix();
      double* right = rh.getMatrix();
      
      //get the dimensions of the Matrix. Assume the vector's main dim is m
      if (!this->isVector())
      {
        m = this->getX;
        n = this->getY;
      }
      else
      {
        m = rh.getX();
        n = rh.getY();
        rhIsVector = false;
      }
      //Malloc the array to temporarily hold the resultant
      resultant = (double*)malloc(n*sizeof(double));
      
      for(int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          if (rhIsVector)
            temp = temp + (lh[i][j] * right[j]);
          else
            temp = temp + (right[i][j] * lh[j]);
        }
        resultant[i] = temp;
        temp = 0;
      }
      if (rhIsVector)
      {
       rh.putMatrix(resultant,1,m);
       return rh;
      }
      else
      {
       this->putMatrix(resultant,1,m); 
       return this;
      } 
    }

    //TODO:Matrix!Matrix multiply and Matrix!scalar multiply
  }

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
  bool isVector()
  {
    if (this.getX() == 1 || this.getY() == 1)
      return true;
    else
      return false;
  }
  double* internal_storage;
  int xDim;
  int yDim;
};
#endif
