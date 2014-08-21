#include "matrixMagic.h"
#include <cmath>
#define internal_storage(r, c) (internal_storage[(r)*xDim + (c)])

Matrix::Matrix()
{
  internal_storage=NULL;
  xDim = yDim = 0;
  isDeletable = true;
}

double Matrix::operator()(const int x, const int y)
{
  return internal_storage(x,y);
}

Matrix Matrix::operator+(Matrix& B)
{
  return mAdd(*this,B);
}

Matrix Matrix::operator*(Matrix& B)
{
  return mMult(*this,B);
}

Matrix::~Matrix()
{
  if (isDeletable)
    delete[] internal_storage;
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
  if (isDeletable)
    delete[] internal_storage;
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
    std::cerr << "\nMatrixMagic: Error in mMult()!! Dimensions are not compatable\n\n";
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
    std::cerr << "\nMatrixMagic: Error in mMult()! A must be a matrix and B must be the vector!\n\n";
    exit(EXIT_FAILURE);
  }

  int n = A.getX();
  int m = A.getY();

  if (n != B.getY())
  {
    std::cerr << "\nMatrixMagic: Error in mMult()! Dimensions are not compatable\n\n";
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

//Matrix mMult(Matrix& A, Matrix& B, int overwrite /*= 1*/)
//{
//  int n;
//  Matrix C;
//  if (A.getX() == B.getY())
//  {
//    if (A.isVector() && !B.isVector())
//    {
//      n = B.getX();
//    }
//    else if (!A.isVector() && B.isVector())
//    {
//      n = A.getX();
//    }
//    else if (A.isVector() && B.isVector())
//    {
//      if (A.getX() != B.getX() && A.getY() != B.getY())
//      {
//        if (A.getX() == B.getY() || A.getY() == B.getX())
//        {
//          if (A.getX() != 1)
//          {
//            n = A.getX();
//          }
//          else
//          {
//            n = A.getY();
//          }
//          if (A.getX() != B.getY() || A.getY() != B.getX())
//          {
//            std::cerr << "\nMatrixMagic: Error in mMult() routine\n\n";
//            exit(EXIT_FAILURE);
//          }
//          double* a_raw = A.getMatrix();
//          double* b_raw = B.getMatrix();
//          double* resultant = new double;
//          double res = 0.0;
//          int i = 0;
//          for (i = 0; i < n; i++)
//          {
//             res += a_raw[i] * b_raw[i];
//          }
//          *resultant = res;
//          if (overwrite == 1)
//          {
//            B.empty();
//            B.setMatrix(resultant,1,1);
//            return B;
//          }
//          else
//          {
//            C.setMatrix(resultant,1,n);
//            return C;
//          }
//        }
//      }
//    }
//    else if (!A.isVector() && !B.isVector())
//    {
//      double* resultant;
//      resultant = squareMatrixMult(A,B);
//      if (overwrite == 1)
//      {
//        B.empty();
//        B.setMatrix(resultant,A.getY(),B.getX());
//        return B;
//      }
//      else
//      {
//        C.setMatrix(resultant,1,n);
//        return C;
//      }
//    }
//    else
//    {
//      std::cerr << "\nMatrixMagic: Error in mMult() routine\n\n";
//      exit(EXIT_FAILURE);
//    }
//  
//    double* a_raw = A.getMatrix();
//    double* b_raw = B.getMatrix();
//    double* resultant = new double[n];
//    double res = 0.0;
//    int i = 0;
//  
//    for (int j = 0; j < n; j++)
//    {
//      for (i = 0; i < n; i++)
//      {
//          res += a_raw[j * n + i] * b_raw[i];
//      }
//      resultant[j] = res;
//      res = 0;
//    }
//    if (overwrite == 1)
//    {
//      B.empty();
//      B.setMatrix(resultant,1,n);
//      return B;
//    }
//    else
//    {
//      C.setMatrix(resultant,1,n);
//      return C;
//    }
//  }
//}

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
}

void solveAxb(Matrix &a, Matrix &B)
{
  if (!B.isVector())
  {
    std::cerr << "\nMatrixMagic: Error in solveAxB(). Second parameter is not a vector!\n\n";
    exit(EXIT_FAILURE);
  }

  Matrix x_0, Ax0, p0, r, r0tr0, r0t_r0_new, alpha_0, temp;
  double* A = a.getMatrix();
  double* b = B.getMatrix();
  double* multiplied;
  int n = a.getX();
  double* x0 = new double[n];
  double* r0tr0_new;
  double* oldPtr;
  double temp2;
  double alpha, beta;

  memset(x0,0,n);
  alpha_0.setMatrix(&alpha,1,1);
  x_0.setMatrix(x0,1,n);
  Ax0 = mMult(a, x_0);
  r = mSub(B,Ax0);     //r0 = b-A*x0
  p0.setMatrix(r.getMatrix(),1,n);
  r.transpose();
  temp = r.transpose();
  r0tr0 = mMult(r,temp);

  for (int k = 0; k < 10^6; k++)
  {
    std::cout << "Solving...\n";
    oldPtr = alpha_0.getMatrix();
    p0.transpose();
    temp = p0.transpose();
    temp = mMult(a,temp);
    alpha = r0tr0.getMatrix()[0]/(mMult(p0,temp)).getMatrix()[0];
    delete[] oldPtr;
    oldPtr = x_0.getMatrix();
    temp = mMult(alpha_0,p0);
    x_0.setMatrix(mAdd(x_0,temp).getMatrix(),1,n);
    delete[] oldPtr;
    oldPtr = r.getMatrix();
    temp = mMult(alpha_0,a);
    temp = mMult(temp,p0);
    r.setMatrix(mSub(r,temp).getMatrix(),1,n);
    delete[] oldPtr;
    oldPtr = r0t_r0_new.getMatrix();
    r.transpose();
    temp = r.transpose();
    r0t_r0_new.setMatrix(mMult(r,temp).getMatrix(),1,1);
    delete[] oldPtr;
    if (sqrt(r0tr0_new[0]) < 1e-10)
      break;
    oldPtr = p0.getMatrix();
    temp2 = mAdd(r,r0t_r0_new).getMatrix()[0]/mMult(r0tr0,p0).getMatrix()[0];
    temp.setMatrix(&temp2,1,1);
    p0.setMatrix(temp.getMatrix(),1,n);
    delete[] oldPtr;
    oldPtr = r0tr0.getMatrix();
    r0tr0.setMatrix(r0tr0_new,1,1);    
    delete[] oldPtr;
  }
}
