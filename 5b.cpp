#include <iostream>
#include <algorithm>
#include <thread>
#include <list>

typedef std::list<int> List;

void square(List & list)
{
		std::for_each(list.begin(), list.end(), [](int & k) 
		    {
						   k *= k; 
						});	
}

int main()
{
std::list<int> list;
		for (int i = 1; i <= 20; i++)
		  list.push_back(i);
  
		std::thread th (&square, std::ref(list));
		th.join();
		
		std::for_each(list.begin(), list.end(), [] (int i) {std::cout << i << "\n";});
}

