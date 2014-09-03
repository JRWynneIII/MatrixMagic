#include <iostream>
#include "matrixMagic.h"
using namespace std;

__global__ void transposeKernel(double* internal_storage)
{
  int tid = blockIdx.x*blockDim.x+threadIdx.x;
  double temp = internal_storage[tid];
  internal_storage[tid] = internal_storage[threadIdx.x * blockDim.x + blockIdx.x];
  internal_storage[threadIdx.x * blockDim.x + blockIdx.x] = temp;
}

void transposeWrapper(double* internal_storage, int m, int n)
{
  double* d_storage;
  cudaMalloc(&d_storage, m*n*sizeof(double));
  cudaMemcpy(d_storage, internal_storage, m*n*sizeof(double), cudaMemcpyHostToDevice);
  transposeKernel<<<n,m>>>(d_storage);
  cudaMemcpy(internal_storage, d_storage, m*n*sizeof(double), cudaMemcpyDeviceToHost);
}
