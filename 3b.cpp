#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>

const int N = 10;


// this will not work in parallel ...
int main()
{
  std::vector<std::thread> workers;
		for (int i = 0; i < N; i++)
		{
				workers.push_back(std::thread([i]()
				{
				  std::cout << "Hello from parallel world at i = " << i << "\n"; 
				}));
		}

		for (int i = 0; i < N; i++)
					std::cout << "Hello from main world at i = " << i << "\n"; 
  
//		std::for_each(workers.begin(), workers.end(), [](std::thread & th){	th.join();}) ;	
		for(auto & th : workers) 
    th.join(); 		
}
