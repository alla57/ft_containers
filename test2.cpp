#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>

int main()
{
	std::vector<int> v(11, 8);
	std::cout << "avant size = " << v.capacity() << std::endl;
	v.push_back(33);
	v.insert
	std::cout << "apres size = " << v.capacity() << std::endl;
	return (0);
}