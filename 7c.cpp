#include <iostream>
#include <vector>
#include <atomic>
#include <thread>

typedef double T;
typedef std::atomic<T> T_ATOMIC; 

void sum_square (T_ATOMIC & result, T x)
{
  	result += x*x;
}


int main()
{
		int N = 6;
		T_ATOMIC x(0);
		std::vector<std::thread> thread_vec;
		for (int i = 1; i <= N; i++)
		  thread_vec.push_back(std::thread(&sum_square, std::ref(x), static_cast<T>(i)));
  
	 for(auto & th : thread_vec)
		  th.join();
		std::cout << "x: " << x <<  "\t" << N*(N+1)*(2*N+1)/6 << "\n";
		
}

