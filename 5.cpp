#include <iostream>
#include <algorithm>
#include <thread>


struct List
{
		struct Node
		{
    int   _data;
				Node* _next;
				Node(int n)
						: _data(n), _next(nullptr) { }
		};

		Node * _root;
		
		List() 
				: _root(nullptr) { }

		void insert(int k)
		{
    auto node = new Node(k);
				node->_next = _root;
				_root = node;
		}
		int size() const 
		{
				int result = 0;
			 auto p = _root;	
    while (p != nullptr)
				{
       result++;
							p = p->_next;
				}
				return result;
		}
};

void threadFunction(List & list, int N = 100)
{
  for(int i = 0; i < N; i++)
				list.insert(i);
}

int main()
{
		int M = 10;
  List list;
		std::vector<std::thread> workers;
		for (int i = 0; i< 10; i++)
				workers.push_back(std::thread(&threadFunction, std::ref(list), M));

		std::for_each(workers.begin(), workers.end(), [](std::thread & th)
						{
         th.join();
						});
		std::cout << list.size() << " , expectig  " << M*10 << "\n";
}

