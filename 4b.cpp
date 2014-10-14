#include<iostream>
#include<thread>
#include<vector>
#include<chrono>


// data race for i

const int N = 10;

void threadFun(int & i)
{
		std::this_thread::sleep_for(std::chrono::microseconds(10000));
		std::cout << "Hello from parallel world at i = " << i << "\n"; 
};

void test(std::vector<std::thread> & workers)
{
		for (int i = 0; i < N; i++)
		{
				workers.push_back(std::thread(threadFun, std::ref(i)));
		}
}

int main()
{
  std::vector<std::thread> workers;
  test(workers);
		for (int i = 0; i < 5; i++)
					std::cout << "Hello from main world " <<  "\n"; 
  
	 for (int i = 0; i < workers.size(); i++)
			workers[i].join();	
 		
}
