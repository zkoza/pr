#include<iostream>
#include<thread>

const int N = 40;

void threadFun()
{
		 for (int i = 0; i < N; i++)
					std::cout << "Hello from parallel world at i = " << i << "\n"; 
}

int main()
{
  std::thread th(&threadFun);
		for (int i = 0; i < N; i++)
					std::cout << "Hello from main world at i = " << i << "\n"; 
//		th.join();
}
