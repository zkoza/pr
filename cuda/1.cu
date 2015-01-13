#include <stdio.h>
#include <assert.h>
#include <cuda.h>
int main(void)
{
  const int N = 1000;
  double *a_h, *b_h;     // pointers to host memory
  double *a_d, *b_d;     // pointers to device memory

  // allocate arrays on host
  a_h = new double [N];
  b_h = new double [N];
  
  // allocate arrays on device
  cudaMalloc((void **) &a_d, sizeof(*a_d)*N);
  cudaMalloc((void **) &b_d, sizeof(*a_d)*N);
  
  // initialize host data
  for (int i=0; i<N; i++) {
    a_h[i] = 10.0+i;
    b_h[i] = 0.0;
  }
  
  // send data from host to device: a_h to a_d
  cudaMemcpy(a_d, a_h, sizeof(double)*N, cudaMemcpyDefault );
  // copy data within device: a_d to b_d
  cudaMemcpy(b_d, a_d, sizeof(double)*N, cudaMemcpyDefault);
  // retrieve data from device: b_d to b_h
  cudaMemcpy(b_h, b_d, sizeof(double)*N, cudaMemcpyDefault);
  // check result
  for (int i=0; i<N; i++)
    assert(a_h[i] == b_h[i]);
  // cleanup
  delete [] a_h; 
  delete [] b_h;
  cudaFree(a_d); 
  cudaFree(b_d);
  printf("Jezeli widzisz ten napis, to program dziala poprawnie\n");
}
