#include <stdio.h>
#include <assert.h>
#include <cuda.h>

// zwykła funkcja w C/C++ 
void incrementArrayOnHost(double *tab, int N)
{
  for (int i=0; i < N; i++) 
    tab[i] += 1.0;
}

// funkcja (tzw. kernel) działająca na GPU
__global__ void incrementArrayOnDevice(double *tab, int N)
{
  int idx = blockIdx.y  * gridDim.x * blockDim.x + blockIdx.x*blockDim.x + threadIdx.x;
//  if (idx < N  && blockIdx.y > 0)
//    printf (" %d %d %d %d %d %d \n", idx,  gridDim.x, blockDim.x, N, blockIdx.x, threadIdx.x);
  if (idx<N) 
     tab[idx] += 1.0;
}



int main(void)
{
  const int N = 100000000;
  printf("N = %d\n", N);
  
  double *a_h, *b_h;     // wskaźniki na pamięć na CPU (host)
  double *a_d;           // wskaźnik na bufor w GPU (device)

  // przydział pamięci na CPU
  a_h = new double [N];
  b_h = new double [N];
  
  // przydział pamięci na GPU
  cudaMalloc((void **) &a_d, sizeof(double)*N);
  
  // inicjalizacja danych na CPU
  for (int i=0; i<N; i++) 
  {
    a_h[i] = i + 1.0;
    b_h[i] = 0;
  }
  
  // przesłąnie danych na GPU: a_h ->  a_d
  cudaMemcpy(a_d, a_h, sizeof(double)*N, cudaMemcpyDefault );
  
  // robimy jakieś obliczenia na CPU
  incrementArrayOnHost(a_h, N);
  
  // a teraz próbujemy zrobić to samo na GPU
  dim3 blockSize = 512;
  dim3 gridSize (1,1,1);
  const int max_block_size = 65535;
  int nBlocks = N/blockSize.x + (N%blockSize.x == 0 ? 0 : 1);
  gridSize.y = 1 + nBlocks/max_block_size;
  gridSize.x = (nBlocks > max_block_size) ? max_block_size : nBlocks;

  printf("%d %d\n", gridSize.x, gridSize.y);

  // wywołujemy kernel na GPU 
  incrementArrayOnDevice <<< gridSize, blockSize >>> (a_d, N);
  // kopiujemy wynik z GPU do CPU
  cudaDeviceSynchronize();
  cudaMemcpy(b_h, a_d, sizeof(double)*N, cudaMemcpyDefault);
  // sprawdzamy wynik
  for (int i=0; i<N; i++) 
  if (a_h[i] != b_h[i] && i < 100)
  {
    printf ("i=%d %g %g\n", i, a_h[i], b_h[i]);
    assert(a_h[i] == b_h[i]);
  }
 
  // sprzątamy
  delete [] a_h; 
  delete [] b_h;
  cudaFree(a_d); 
  printf("Jeżeli widzisz ten napis, to program działa poprawnie\n");
}
