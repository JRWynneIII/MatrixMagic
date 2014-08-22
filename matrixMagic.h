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
  Matrix();
  Matrix(const Matrix& rhs);
  ~Matrix();

  Matrix transpose();
  double operator()(const int x, const int y);
  Matrix operator+(Matrix& B);
  Matrix operator-(Matrix& B);
  Matrix operator*(Matrix& B);
  Matrix& operator=(const Matrix& B);
  void readMatrix(const char* filename);
  void setMatrix(double* external, int x, int y);
  void LUDecomp(Matrix &l, Matrix &u);
  double* getMatrix();
  void printMatrix();
  int getX();
  int getY();
  bool isVector();
  void empty();

private:
  double* internal_storage;
  int xDim;
  int yDim;
  bool isDeletable;
};

double* squareMatrixMult(Matrix A, Matrix B);
Matrix mMult(Matrix& A, Matrix& B, int overwrite = 0);
Matrix mAdd(Matrix& A, Matrix& B, int overwrite = 0);
Matrix mSub(Matrix& A, Matrix& B, int overwrite = 0);
void solveAxb(Matrix& A, Matrix& B);

#endif
