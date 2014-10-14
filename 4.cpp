#include<iostream>
#include<thread>
#include<vector>


const int N = 10;

void threadFun(int  i)
{
		std::cout << "Hello from parallel world at i = " << i << "\n"; 
};

int main()
{
  std::vector<std::thread> workers;
		for (int i = 0; i < N; i++)
		{
				workers.push_back(std::thread(threadFun,  i));
		}

		for (int i = 0; i < N; i++)
					std::cout << "Hello from main world at i = " << i << "\n"; 
  
	 for (int i = 0; i < N; i++)
			workers[i].join();	
 		
}
