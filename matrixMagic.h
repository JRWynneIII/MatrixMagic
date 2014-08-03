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
  void LUDecomp();
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
};

double* squareMatrixMult(Matrix A, Matrix B);
void multiply(Matrix& A, Matrix& B);

#endif
