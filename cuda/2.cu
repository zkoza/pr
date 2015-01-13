#include <stdio.h>
#include <assert.h>
#include <cuda.h>


#define CHECK_CUDA(x)           \
{                               \
  cudaError_t err = x;          \
  if (err != cudaSuccess)       \
  {                             \
     printf("!!! CUDA ERROR: \"%s\" at file %s, line %d !!!\n", cudaGetErrorString(err), __FILE__, __LINE__);\
     exit(1);                   \
  }                             \
}

int main(int argc, char* argv[])
{
  const int N = (argc==1)?  10000 : atoi(argv[1]);
  printf("N = %d\n", N);

  double *a_h, *b_h;     // pointers to host memory
  double *a_d, *b_d;     // pointers to device memory

  // allocate arrays on host
  a_h = new double [N];
  b_h = new double [N];
  
  // allocate arrays on device
  CHECK_CUDA( cudaMalloc((void **) &a_d, sizeof(double)*N) );
  CHECK_CUDA( cudaMalloc((void **) &b_d, sizeof(double)*N) );
  
  // initialize host data
  for (int i=0; i<N; i++) {
    a_h[i] = 10.f+i;
    b_h[i] = 0.f;
  }
  
  // send data from host to device: a_h to a_d
  CHECK_CUDA( cudaMemcpy(a_d, a_h, sizeof(double)*N, cudaMemcpyDefault) );
  // copy data within device: a_d to b_d
  CHECK_CUDA( cudaMemcpy(b_d, a_d, sizeof(double)*N, cudaMemcpyDefault) );
  // retrieve data from device: b_d to b_h
  CHECK_CUDA( cudaMemcpy(b_h, b_d, sizeof(double)*N, cudaMemcpyDefault) );
  // check result
  for (int i=0; i<N; i++)
    assert(a_h[i] == b_h[i]);
  // cleanup
  delete [] a_h; 
  delete [] b_h;
  CHECK_CUDA( cudaFree(a_d) ); 
  CHECK_CUDA( cudaFree(b_d) );
  printf("Gratulacje, program dziala poprawnie!!!\n");
}
