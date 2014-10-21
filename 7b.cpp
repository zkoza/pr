#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

std::mutex mut;

void sum_square (double & result, double x)
{
		 double tmp = x*x;
		 mut.lock();
  	result += tmp;
			mut.unlock();
}


int main()
{
		int N = 6;
		double x = 0.0;
		std::vector<std::thread> thread_vec;
		for (int i = 1; i <= N; i++)
		  thread_vec.push_back(std::thread(&sum_square, std::ref(x), static_cast<double>(i)));
  
	 for(auto & th : thread_vec)
		  th.join();
		std::cout << "x: " << x <<  "\t" << N*(N+1)*(2*N+1)/6 << "\n";
		
}

