#include<iostream>
#include<thread>

const int N = 40;

int main()
{
  std::thread th([]()
		{
		  for (int i = 0; i < N; i++)
				  std::cout << "Hello from parallel world at i = " << i << "\n"; 
		});

		for (int i = 0; i < N; i++)
					std::cout << "Hello from main world at i = " << i << "\n"; 
		th.join();
}
