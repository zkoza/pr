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
  int idx = blockIdx.x*blockDim.x + threadIdx.x;
  if (idx<N) 
     tab[idx] += 1.0;
}



int main(void)
{
  const int N = 10000000;
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
    a_h[i] = 1.0/(i + 1.0);
  }
  
  // przesłąnie danych na GPU: a_h ->  a_d
  cudaMemcpy(a_d, a_h, sizeof(double)*N, cudaMemcpyDefault );
  
  // robimy jakieś obliczenia na CPU
  incrementArrayOnHost(a_h, N);
  
  // a teraz próbujemy zrobić to samo na GPU
  int blockSize = 320;
  int nBlocks = N/blockSize + (N%blockSize == 0 ? 0 : 1);
  // wywołujemy kernel na GPU 
  incrementArrayOnDevice <<< nBlocks, blockSize >>> (a_d, N);
  // kopiujemy wynik z GPU do CPU
  cudaMemcpy(b_h, a_d, sizeof(double)*N, cudaMemcpyDefault);
  // sprawdzamy wynik
  for (int i=0; i<N; i++) 
     assert(a_h[i] == b_h[i]);
 
  // sprzątamy
  delete [] a_h; 
  delete [] b_h;
  cudaFree(a_d); 
  printf("Jeżeli widzisz ten napis, to program działa poprawnie\n");
}
