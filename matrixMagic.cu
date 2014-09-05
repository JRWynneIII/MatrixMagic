#include <iostream>
#include "matrixMagic.h"
using namespace std;

#define internal_storage(r, c) (internal_storage[(r)*n + (c)])
#define output(r, c) (output[(r)*n + (c)])

void CUDAErrorCheck()
{
  cudaError_t error = cudaGetLastError();
  if (error != cudaSuccess)
  {
    cout << "CUDA error : " << cudaGetErrorString(error) << " (" << error << ")\n";
    exit(EXIT_FAILURE);
  }
}

__global__ void transposeKernel(double* internal_storage, int m, int n, double* output)
{
  int tid = threadIdx.x;
  for(int j = tid+1; j < n; j++)
  {
    double temp = internal_storage(tid,j);
    internal_storage(tid, j) = internal_storage(j,tid);
    internal_storage(j,tid) = temp;
  }
}

void transposeWrapper(double* internal_storage, int m, int n)
{
  double* d_storage;
  double* d_output;

  cudaMalloc(&d_storage, m*n*sizeof(double));
  cudaMalloc(&d_output, m*n*sizeof(double));
  cudaMemcpy(d_storage, internal_storage, m*n*sizeof(double), cudaMemcpyHostToDevice);
  CUDAErrorCheck();
  transposeKernel<<<1,m*n>>>(d_storage,m,n,d_output);
  cudaMemcpy(internal_storage, d_storage, m*n*sizeof(double), cudaMemcpyDeviceToHost);
  CUDAErrorCheck();
}
