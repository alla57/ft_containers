#include <vector>
#include <iostream>
#include <iterator>
#include "Iterator.hpp"
#include "Utilities.hpp"
// #include <type_traits>
#include <stdint.h>

bool	j(int v)
{
	if (v == 25)
		return (true);
	return (false);
}

template<typename pred>
void abc(pred p)
{
	if (p(25))
		std::cout << "oui" << std::endl;
	else
		std::cout << "non" << std::endl;
}

int main()
{
	abc<bool(*)(int)>(j);
	return (0);
}

/*
int main()
{
	std::vector<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	a.push_back(7);
	// std::vector<int>::iterator it;
	// it = a.begin();
	// it--;
	std::reverse_iterator<std::vector<int>::iterator> rev_it(a.begin());
	// rev_it = a.begin();

	std::cout << rev_it[-1] << std::endl;
	// std::cout << &(*it) << std::endl;

	// std::cout << &(*(a.end())) << std::endl;
	// std::cout << &(*rev_it) << std::endl;

	// std::vector<int>::iterator it;
	// it = a.begin();
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;
	// it++;
	// std::cout << *it << std::endl;

	// std::cout << *rev_it << std::endl;
	// rev_it--;
	// std::cout << *rev_it << std::endl;
	// rev_it--;
	// std::cout << *rev_it << std::endl;
	return (0);
}*/