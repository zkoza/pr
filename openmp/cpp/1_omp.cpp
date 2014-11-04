#include <iostream>
#include <vector>
#include <omp.h>


int main()
{
#pragma omp parallel
		{
    std::cout << "Hello world frm " 
						        << omp_get_thread_num() 
														<< "\n";
		}
		std::cout << "hello from main\n";
		
		const int N = 1000000000;

		double sum = 0.0;
#pragma omp parallel shared(sum) 
		{

#pragma omp single
				{
						std::cout << "Program jest wykonywany na " 
								<< omp_get_num_threads() 
								<<  " watkach.\n";
				}

#pragma omp for	reduction (+ : sum)
				for (int i = 1; i < N; i++)
						sum +=  1.0/i;

#pragma omp single 
    std::cout << "suma = " << sum << "\n";
		}


		std::cout << "hello from main again!\n";
}
