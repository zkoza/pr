#include<iostream>
#include<thread>

const int N = 10;


// this will not work in parallel ...
int main()
{
		for (int i = 0; i < N; i++)
		{
				std::thread th([i]()
				{
				  std::cout << "Hello from parallel world at i = " << i << "\n"; 
				});
				// local scope -> destructors!
				th.join();
		}

		for (int i = 0; i < N; i++)
					std::cout << "Hello from main world at i = " << i << "\n"; 
	 
}
