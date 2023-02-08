#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>

int main()
{
	std::vector<int> v(10, 8);
	std::vector<int> u(11, 8);
	u.reserve(12);
	v.push_back(9);
	u.push_back(10);
	u.push_back(10);
	if (u < v)
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	if (std::lexicographical_compare(u.begin(), u.end(), v.begin(), v.end()))
		std::cout << "yes" << std::endl;
	else
		std::cout << "no" << std::endl;
	// std::cout << v.size() << std::endl;
	return (0);
}