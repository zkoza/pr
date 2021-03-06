#include <iostream>
#include <algorithm>
#include <thread>
#include <list>
#include <future>
#include <cmath>

typedef std::list<int> List;

void length(List && list, std::promise<double> && prom)
{
  double sum = 0;
		std::for_each(list.begin(), list.end(), [&sum](int k) 
		    {
						   double x = k;
						   sum += x*x;
						});	
  prom.set_value(std::sqrt(sum));
}

int main()
{
		std::list<int> list;
		for (int i = 1; i <= 20; i++)
		  list.push_back(i);
  
		std::promise<double> prom;
  std::future <double> fut = prom.get_future();
		std::thread th (&length, std::move(list), std::move(prom));
		std::cout << "length: " << fut.get() << "\n";
		th.join();
		
}

