#include "matrixMagic.h"
#include <cmath>

Matrix::Matrix()
{
  internal_storage=NULL;
  xDim = yDim = 0;
  isDeletable = true;
}

//Copy constructor

Matrix::Matrix(const Matrix& rhs)
{
  internal_storage = new double[(rhs.xDim) * (rhs.yDim)];
  memcpy(internal_storage, rhs.internal_storage,(rhs.xDim)*(rhs.yDim)*sizeof(double));
  isDeletable = true;
  xDim = rhs.xDim;
  yDim = rhs.yDim;
}

#define internal_storage(r, c) (internal_storage[(r)*xDim + (c)])

Matrix::~Matrix()
{
  if (internal_storage == NULL)
    return;
  if (isDeletable)
  {
    delete[] internal_storage;
    internal_storage = NULL;
  }
}

double Matrix::operator()(const int x, const int y)
{
  return internal_storage(x,y);
}

Matrix Matrix::operator+(const Matrix& B)
{
  Matrix b = B;
  return mAdd(*this,b);
}

Matrix Matrix::operator*(const Matrix& B)
{
  Matrix b = B;
  return mMult(*this,b);
}

Matrix Matrix::operator-(const Matrix& B)
{
  Matrix b = B;
  return mSub(*this,b);
}

Matrix& Matrix::operator=(const Matrix& B)
{
  if (this != &B)
  {
    this->empty();
    internal_storage = new double[(B.xDim)*(B.yDim)];
    memcpy(internal_storage,B.internal_storage,(B.xDim)*(B.yDim)*sizeof(double));
    isDeletable = true;
    xDim = B.xDim;
    yDim = B.yDim;
  }
  return *this;
}

Matrix& Matrix::operator=(const double& B)
{
  this->empty();
  *internal_storage = B;
  isDeletable = false;
  xDim = 1;
  yDim = 1;
  return *this;
}
Matrix Matrix::transpose()
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
  return *this;
}

void Matrix::read(const char* filename)
{
  this->readMatrix(filename);
}

void Matrix::print()
{
  this->printMatrix();
}
void Matrix::readMatrix(const char* filename)
{
  int x = 0;
  int y = 0;
  //measure matrix size
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
  matrixFile.clear();
  matrixFile.seekg(0);

  while(!matrixFile.eof())
  {
    getline(matrixFile, c);
    ySize++;
  }
  ySize--;
  internal_storage = new double[xSize*ySize];
  matrixFile.clear();
  matrixFile.seekg(0);
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
  internal_storage = external;
  xDim = x;
  yDim = y;
}
#define L(r, c) (L[(r)*xDim + (c)])
#define U(r, c) (U[(r)*xDim + (c)])
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
  if (internal_storage == NULL)
    return;
  if (isDeletable)
  {
    delete[] internal_storage;
    internal_storage = NULL;
  }
}

#define resultant(r, c) (resultant[(r)*n + (c)])
#define Aptr(r, c) (Aptr[(r)*n + (c)])
#define Bptr(r, c) (Bptr[(r)*n + (c)])

void doubleVector(Matrix& A, Matrix& B, double* resultant)
{
  int res = 0;
  int n;
  if (A.getX() == 1)
    n = A.getY();
  else if (A.getY() == 1)
    n = A.getX();
  for (int i = 0; i < n; i++)
    res += A(0,i) * B(0,i);
  *resultant = res;
}

void doubleMatrix(Matrix& A, Matrix& B, double* resultant)
{
  int k = 0;
  double res = 0;

  int nA = A.getX();
  int mA = A.getY();
  int nB = B.getX();
  int mB = B.getY();
  int n = mB;
  int m = nA;

  if (n != B.getY())
  {
    std::cerr << "\nMatrixMagic: Error in mMult()!! Dimensions are not compatable\nA: Matrix: X: " << A.getX() << " Y: " << A.getY() << "\n";
    std::cerr << "B: Matrix: X: " << B.getX() << " Y: " << B.getY() << "\n\n"; 
    exit(EXIT_FAILURE);
  }

  
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      for (k = 0; k < m; k++) 
      {
        res += A(i,k) * B(k,j);
      }
      resultant(i,j) = res;
      res = 0;
    }
  }
}

void matrixVector(Matrix& A, Matrix& B, double* resultant)
{
  double res = 0;
  int i = 0;
  if (A.isVector())
  {
    std::cerr << "\nMatrixMagic: Error in mMult()!! Dimensions are not compatable\nA: Matrix: X: " << A.getX() << " Y: " << A.getY() << "\n";
    std::cerr << "B: Vector: X: " << B.getX() << " Y: " << B.getY() << "\n\n"; 
    exit(EXIT_FAILURE);
  }

  int n = A.getX(); //Columns
  int m = A.getY(); //Rows

  if (n != B.getY()) //If A's columns are not equal to B's rows
  {
    std::cerr << "\nMatrixMagic: Error in mMult()!! Dimensions are not compatable\nA: Matrix: X: " << A.getX() << " Y: " << A.getY() << "\n";
    std::cerr << "B: Vector: X: " << B.getX() << " Y: " << B.getY() << "\n\n"; 
    exit(EXIT_FAILURE);
  }

  for (int j = 0; j < n; j++)
  {
    for (i = 0; i < n; i++)
    {
        res += A(j,i) * B(0,i);
    }
    resultant[j] = res;
    res = 0;
  }
}

Matrix mMult(Matrix& A, Matrix& B, int overwrite)
{
  Matrix C;
  int n,m;
  int nA, nB, mA, mB;
  double res = 0;
  double* Aptr = A.getMatrix();
  double* Bptr = B.getMatrix();
  double* resultant;

  
  mA = A.getY();
  mB = B.getY();
  nA = A.getX();
  nB = B.getX();

  //size of final matrix
  m = nA;
  n = mB;

  resultant = new double[m*n];
  //row * column
  int i = 0;
  if ((A.isVector() && !B.isVector()) || (!A.isVector() && B.isVector()))
  {
    matrixVector(A,B,resultant);
    m = 1;
  }
  else if (A.isVector() && B.isVector())
  {
    doubleVector(A,B,resultant);
    m = 1;
    n = 1;
  }
  else
  {
    doubleMatrix(A,B,resultant);
  }

  if (overwrite == 1)
  {
    B.setMatrix(resultant,m,n);
    return B;
  }
  else
  {
    C.setMatrix(resultant,m,n);
    return C;
  }

}

#define b(r, c) (b[(r)*n + (c)])
#define a(r, c) (a[(r)*n + (c)])
#define c(r, d) (c[(r)*n + (d)])
Matrix mAdd(Matrix &A, Matrix &B, int overwrite /*=1*/)
{
  //Writes answer over B
  Matrix C;
  int n = A.getX();
  int m = A.getY();
  double* a = A.getMatrix();
  double* b = B.getMatrix();
  double* c = new double[n*m];
  if (n != B.getX() || m != B.getY())
  {
    std::cerr << "\nMatrixMagic: Error in matrix mAdd(). Incompatable Matrices\n\n";
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < m; i++) //y
  {
    for(int j = 0; j < n; j++) //x
    {
      c(j,i) = a(j,i) + b(j,i);
    }
  }
  if (overwrite == 1)
  {
    B.empty();
    B.setMatrix(c,m,n);
  }
  else
  {
    C.setMatrix(c,m,n);
    return C;
  }
  Matrix EMPTY;
  return EMPTY; //To remove error when compiling with CLANG on Mac
}

Matrix mSub(Matrix &A, Matrix &B, int overwrite /*=1*/)
{
  //Writes answer over B
  Matrix C;
  int n = A.getX();
  int m = A.getY();
  double* a = A.getMatrix();
  double* b = B.getMatrix();
  double* c = new double[n*m];
  if (n != B.getX() || m != B.getY())
  {
    std::cerr << "\nMatrixMagic: Error in matrix mSub(). Incompatable Matrices\n\n";
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < m; i++) //y
  {
    for(int j = 0; j < n; j++) //x
    {
      c(j,i) = a(j,i) - b(j,i);
    }
  }
  if (overwrite == 1)
  {
    B.empty();
    B.setMatrix(c,m,n);
  }
  else
  {
    C.setMatrix(c,m,n);
    return C;
  }
  Matrix EMPTY;
  return EMPTY; //To remove error when compiling with CLANG on Mac
}

Matrix solveAxb(Matrix &A, Matrix &b)
{
  Matrix r0, p0, x0, r1, alpha, rsold, rsnew;
  int k = 0;
  double* initialGuess = new double[A.getX()];
  for (int i = 0; i < A.getX(); i++)
  {
    initialGuess[i] = i+1;
  }
  x0.setMatrix(initialGuess,1,A.getX());
  
  r0 = b - (A*x0);
  p0 = r0;

  rsold = r0.transpose() * r0.transpose();

  for (k = 0; k < 1e6; k++)
  {
    alpha = (rsold.getMatrix()[0])/(p0.transpose()*(A*p0.transpose())).getMatrix()[0];
    x0 = x0 + (alpha * p0);
    r1 = r0 - (alpha*(A*p0));
    rsnew = (r1.transpose() * r1.transpose());

    if (rsnew.getMatrix()[0] < 1e-10)
      return x0;

    p0 = (r1 + rsnew).getMatrix()[0] / (rsold*p0).getMatrix()[0];
    rsold = rsnew;
  }
  
  delete[] initialGuess;
  return x0; //Just in case it takes all 1e6 iterations to get to the end. And to make Clang shut up with warnings
}
