#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>

#include "Vector.hpp"
// #include "TypeTraits.hpp"

int main()
{
	std::vector<int> vct(7);
	std::vector<int> v(7, 9);
	ft::vector<int> uct(7);
	vct.insert(vct.begin(), v.begin(), v.end())
	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct.at(): " << vct.at(i) << " | ";
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	for (unsigned long int i = 0; i < uct.size(); ++i)
	{
		uct.at(i) = (uct.size() - i) * 3;
		std::cout << "uct.at(): " << uct.at(i) << " | ";
		std::cout << "uct[]: " << uct[i] << std::endl;
	}
	std::cout << vct.capacity() << std::endl;
	std::cout << vct.size() << std::endl;
	std::cout << uct.capacity() << std::endl;
	std::cout << uct.size() << std::endl;
	try {
		uct.at(10) = 42;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	return (0);
}