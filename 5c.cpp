#include <iostream>
#include <algorithm>
#include <thread>
#include <list>
#include <cmath>

typedef std::list<int> List;

void square(List & list)
{
		std::for_each(list.begin(), list.end(), [](int & k) 
		    {
					    k *= k; 
         for(int i = 0; i < 200; i++)
									{
									  double x = k;
											x *= x;
											x = std::sqrt(x);
											k = x;
									}
						});	
}

int main()
{
std::list<int> list;
		for (int i = 1; i <= 20; i++)
		  list.push_back(i);
  
		std::thread th (&square, std::ref(list));
		// XXX race !!!
		std::for_each(list.begin(), list.end(), [] (int i) 
						{
						   std::cout << i << "\n";
						});
		th.join();
		
}

