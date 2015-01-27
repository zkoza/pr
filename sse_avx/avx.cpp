#include <immintrin.h> // AVX
#include <emmintrin.h>
#include <iostream>
#include <cmath>

void calc_sse (double* wynik, double* p1, double* p2, int size)
{
  __m128d asse, bsse;
  const __m128d sse_pol = _mm_set_pd1(0.5);
  for (int i = 0; i < size; i += 2)
  {
    asse = _mm_load_pd( &p1[i] );
    bsse = _mm_load_pd( &p2[i] );
    asse = _mm_mul_pd( asse, asse );
    bsse = _mm_mul_pd( bsse, bsse );
    asse = _mm_add_pd( asse, bsse);
    asse = _mm_sqrt_pd( asse );
    asse = _mm_add_pd(asse, sse_pol);
    _mm_store_pd( &wynik[i], asse);
  }
}

double sse(int N)
{
   double wynik = 0;
   __m128d asse, bsse, sumsse;
   const __m128d sse1 = _mm_set_pd1(1.0);
   sumsse = _mm_set_pd1(0.0);

   for (int i = 0; i < N; i += 2)
   {
     asse = _mm_set_pd(i, i + 1);
     bsse = asse;
     asse = _mm_mul_pd(asse, asse);
     asse = _mm_mul_pd(asse, bsse);
     asse = _mm_add_pd(asse, sse1);
     asse = _mm_sqrt_pd(asse);
     asse = _mm_div_pd(sse1, asse);
     sumsse = _mm_add_pd(sumsse, asse);
   }
   double x =  _mm_cvtsd_f64(sumsse);
   double y =  _mm_cvtsd_f64(_mm_unpackhi_pd(sumsse, sumsse));
   wynik = x + y;
   return wynik;
}

double  cpp(int N)
{
  double x = 0.0;
  for (int i = 0; i < N; i++)
  {
    double y = i;
    x += 1.0/sqrt(y*y*y+1.0);
  }
  return x;
}


int main()
{
  int N = 500000000; 
  std::cout << sse(N) << "\n";
//  std::cout << cpp(N) << "\n";

}
