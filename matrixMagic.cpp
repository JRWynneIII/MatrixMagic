#include "matrixMagic.h"
#define internal_storage(r, c) (internal_storage[(r)*xDim + (c)])

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

Matrix& Matrix::transpose()
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

double* squareMatrixMult(Matrix A, Matrix B)
{
  int n,m;
  int nA, nB, mA, mB;
  double res = 0;
  double* Aptr = A.getMatrix();
  double* Bptr = B.getMatrix();
  double* resultant;

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

Matrix mMult(Matrix& A, Matrix& B, int overwrite /*= 1*/)
{
  int n;
  Matrix C;
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
          if (A.getX() != B.getY() || A.getY() != B.getX())
          {
            std::cerr << "\nMatrixMagic: Error in mMult() routine\n\n";
            exit(EXIT_FAILURE);
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
          if (overwrite == 1)
          {
            B.empty();
            B.setMatrix(resultant,1,1);
            return B;
          }
          else
          {
            C.setMatrix(resultant,1,n);
            return C;
          }
        }
      }
    }
    else if (!A.isVector() && !B.isVector())
    {
      double* resultant;
      resultant = squareMatrixMult(A,B);
      if (overwrite == 1)
      {
        B.empty();
        B.setMatrix(resultant,A.getY(),B.getX());
        return B;
      }
      else
      {
        C.setMatrix(resultant,1,n);
        return C;
      }
    }
    else
    {
      std::cerr << "\nMatrixMagic: Error in mMult() routine\n\n";
      exit(EXIT_FAILURE);
    }
  
    double* a_raw = A.getMatrix();
    double* b_raw = B.getMatrix();
    double* resultant = new double[n];
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
    if (overwrite == 1)
    {
      B.empty();
      B.setMatrix(resultant,1,n);
      return B;
    }
    else
    {
      C.setMatrix(resultant,1,n);
      return C;
    }
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
//  if (!B.isVector())
//  {
//    std::cerr << "\nMatrixMagic: Error in solveAxB(). Second parameter is not a vector!\n\n";
//    exit(EXIT_FAILURE);
//  }
//
//  Matrix x_0, Ax_0, p_0, r_0, r0t_r0, r0t_r0_new, alpha_0;
//  double* A = a.getMatrix();
//  double* b = B.getMatrix();
//  double* multiplied;
//  int n = a.getX();
//  double* x0 = new double[n];
//  double* r;
//  double* r0tr0;
//  double* r0tr0_new;
//  double* oldPtr;
//  double* Ax0;
//  double* p0 = new double[n];
//  double* alpha, beta;
//
//  memset(x0,0,n);
//  memset(alpha,0,n);
//  alpha_0.setMatrix(alpha,1,1);
//  x_0.setMatrix(x0,1,n);
//  Ax0 = mMult(a, x_0, 0);
//  Ax_0.setMatrix(Ax0,1,n);
//  r = mSub(B,Ax_0,0);     //r0 = b-A*x0
//  memcpy(p0,r,n);         //p0 = r
//  r_0.setMatrix(r,1,n);
//  p_0.setMatrix(p0,1,n);
//  r0tr0 = mMult(r_0.transpose(),r_0.transpose(),0);
//
//  for (int k = 0; k < 10^6; k++)
//  {
//    std::cout << "Solving...\n";
//    oldPtr = alpha_0.getMatrix();
//    alpha = r0tr0[0]/mMult(p_0.transpose(),mMult(a,p_0.transpose(),0),0);
//    delete[] oldPtr;
//    oldPtr = x_0.getMatrix();
//    x_0.setMatrix(mAdd(x_0,mMult(alpha_0,p_0,0),0),1,n);
//    delete[] oldPtr;
//    oldPtr = r_0.getMatrix();
//    r_0.setMatrix(mSub(r_0,mMult(mMult(alpha_0,a,0),p_0,0),0),1,n);
//    delete[] oldPtr;
//    oldPtr = r0t_r0_new.getMatrix();
//    r0t_r0_new.setMatrix(mMult(r_0.transpose(),r_0.transpose(),0),1,1);
//    delete[] oldPtr;
//    if (sqrt(r0tr0_new[0]) < 1e-10)
//      break;
//    oldPtr = p_0.getMatrix();
//    p_0.setMatrix(mAdd(r_0,r0_tr0_new,0)/mMult(r0t_r0,p_0,0),1,n);
//    delete[] oldPtr;
//    oldPtr = r0t_r0.getMatrix();
//    r0t_r0.setMatrix(r0tr0_new,1,1);    
//    delete[] oldPtr;
//  }
//  return x0;
//  delete[] x0,x1,r0,r1,p0,p1,alpha,beta;
}
