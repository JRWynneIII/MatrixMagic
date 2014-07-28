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

  void LUDecomp()
  {
    double* U = new double[xDim * yDim];
    double* L = new double[xDim * yDim];
    int i, j;
    //Loop through internal_storage and seperate the lower triangular matrix and upper triangular matrix into L and U respectively
    for (i = 0; i < yDim; i++)
    {
      for (j = 0; j < xDim; j++)
      {
        if (j > i)
        {
          U[xDim * i + j] = internal_storage[xDim * i + j];
          L[xDim * i + j] = 0;
        }
        else if (j == i)
        {
          U[xDim * i + j] = internal_storage[xDim * i + j];
          L[xDim * i + j] = internal_storage[xDim * i + j];
        }
        else
        {
          L[xDim * i + j] = internal_storage[xDim * i + j];
          U[xDim * i + j] = 0;
        }
      }
    }
    
    for (i = 0; i < yDim; i++)
    {
      for (j = 0; j < xDim; j++)
      {
        std::cout << U[xDim * i + j] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    for (i = 0; i < yDim; i++)
    {
      for (j = 0; j < xDim; j++)
      {
        std::cout << L[xDim * i + j] << " ";
      }
      std::cout << std::endl;
    }
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

void multiply(Matrix& A, Matrix& B)
{
  int n;
  if (A.getX() == B.getY())
  {
    if (A.isVector() && !B.isVector())
    {
      n = B.getX();
    }
    else if (!A.isVector() && B.isVector())
    {
      n = A.getX();
    }
    else if (A.isVector() && B.isVector())
    {
      if (A.getX() != B.getX() && A.getY() != B.getY())
      {
        if (A.getX() == B.getY() || A.getY() == B.getX())
        {
          if (A.getX() != 1)
          {
            n = A.getX();
          }
          else
          {
            n = A.getY();
          }
          double* a_raw = A.getMatrix();
          double* b_raw = B.getMatrix();
          double* resultant = new double;
          double res = 0.0;
          int i = 0;
          for (i = 0; i < n; i++)
          {
             res += a_raw[i] * b_raw[i];
          }
          *resultant = res;
          B.setMatrix(resultant,1,1);
          return;
        }
      }
    }
    else
    {
      std::cerr << "\nError in multiply() routine of MatrixMagic!\n\n";
      exit(EXIT_FAILURE);
    }
  
    double* a_raw = A.getMatrix();
    double* b_raw = B.getMatrix();
    double* resultant = (double*)malloc(n*sizeof(double));
    double res = 0.0;
    int i = 0;
  
    for (int j = 0; j < n; j++)
    {
      for (i = 0; i < n; i++)
      {
          res += a_raw[j * n + i] * b_raw[i];
      }
      resultant[j] = res;
      res = 0;
    }
  
    B.setMatrix(resultant,1,n);
  }
}

#endif
