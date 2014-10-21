#include <iostream>
#include <algorithm>
#include <thread>
#include <list>
#include <future>
#include <cmath>

typedef std::list<int> List;

double length(List & list)
{
  double sum = 0;
		std::for_each(list.begin(), list.end(), [&sum](int k) 
		    {
						   double x = k;
						   sum += x*x;
						});	
 return std::sqrt(sum);
}

int main()
{
		std::list<int> list;
		for (int i = 1; i <= 20; i++)
		  list.push_back(i);
  
  std::future <double> fut = std::async(length, std::ref(list));
		std::cout << "length: " << fut.get() << "\n";
		std::cout << "good bye\n";
}

