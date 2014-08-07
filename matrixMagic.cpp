#include "matrixMagic.h"

Matrix::Matrix()
{
  internal_storage=NULL;
  xDim = yDim = 0;
  isDeletable = true;
}

Matrix::~Matrix()
{
  if (isDeletable)
    delete[] internal_storage;
}

void Matrix::transpose()
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
void Matrix::readMatrix(const char* filename)
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
  isDeletable = true;
}

void Matrix::setMatrix(double* external, int x, int y)
{
  isDeletable = false;
  internal_storage = NULL;
  internal_storage = external;
  xDim = x;
  yDim = y;
}
#define L(r, c) (L[(r)*xDim + (c)])
#define U(r, c) (U[(r)*xDim + (c)])
#define internal_storage(r, c) (internal_storage[(r)*xDim + (c)])
void Matrix::LUDecomp(Matrix &l, Matrix &u)
{
  l.empty();
  u.empty();

  double* U = new double[xDim * yDim];
  double* L = new double[xDim * yDim];

  int i, j, k;
  int n = xDim;

  for (k = 0; k < n ; k++) 
  {
    L(k,k) = 1;
    for (i = k + 1; i < n ; i ++)
    {
      L(i,k) = internal_storage(i,k)/internal_storage(k,k);

      for (j = k + 1; j < n ; j ++) 
      {
        internal_storage(i,j) = internal_storage(i,j) - L(i,k)*internal_storage(k,j);
      }
    }
    for (j = k; j < n ; j++) 
    {
      U(k,j) = internal_storage(k,j);
    }
  }
  
  l.setMatrix(L,xDim,yDim);
  u.setMatrix(U,xDim,yDim);
}

double* Matrix::getMatrix()
{
  return internal_storage;
}
void Matrix::printMatrix()
{
  for (int y = 0; y < yDim; y++)
  {
    for (int x = 0; x < xDim; x++)
      cout << fixed << internal_storage[xDim * y + x] << " ";
    cout << endl;
  }
}

int Matrix::getX()
{
  return xDim;
}

int Matrix::getY()
{
  return yDim;
}

bool Matrix::isVector()
{
  if (this->getX() == 1 || this->getY() == 1)
    return true;
  else
    return false;
}

void Matrix::empty()
{
  if (isDeletable)
    delete[] internal_storage;
  else
  {
    std::cerr << "\nMatrixMagic: Error in empty() method!\n\n";
    exit(EXIT_FAILURE);
  }
}

double* squareMatrixMult(Matrix A, Matrix B)
{
  int n,m;
  int nA, nB, mA, mB;
  double res = 0;
  double* Aptr = A.getMatrix();
  double* Bptr = B.getMatrix();
  double* resultant;

  //test to see if they're multiplyable
  if (A.getX() != B.getY())
  {
    std::cerr << "\nMatrixMagic: Error in squareMatrixMult()! Dimensions are not compatable\n\n";
    exit(EXIT_FAILURE);
  }
  
  mA = A.getY();
  mB = B.getY();
  nA = A.getX();
  nB = B.getX();

  //size of final matrix
  m = mA;
  n = nB;

  resultant = new double[m*n];
  //row * column
  int k = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      for (k = 0; k < m; k++) 
      {
        res += Aptr[i * m + k] * Bptr[k * m + j];
      }
      resultant[i * m + j] = res;
      res = 0;
    }
  }
  return resultant;
}

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
    else if (!A.isVector() && !B.isVector())
    {
      double* resultant = new double;
      resultant = squareMatrixMult(A,B);
      B.setMatrix(resultant,A.getY(),B.getX());
      return;
    }
    else
    {
      std::cerr << "\nMatrixMagic: Error in multiply() routine\n\n";
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
