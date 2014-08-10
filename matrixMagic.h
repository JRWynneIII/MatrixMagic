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
  ~Matrix();

  void transpose();
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
double* mMult(Matrix& A, Matrix& B, int overwrite = 1);
double* mAdd(Matrix& A, Matrix& B, int overwrite = 1);
double* mSub(Matrix& A, Matrix& B, int overwrite = 1);
void solveAxb(Matrix& A, Matrix& B);

#endif
