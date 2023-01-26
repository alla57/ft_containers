#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>

int main()
{
	std::vector<int> v(10, 8);
	std::cout << v.capacity() << std::endl;
	// std::__throw_length_error(__N("cannot create std::vector larger than max_size()"));
	// throw(std::length_error("cannot create std::vector larger than max_size()"));
	return (0);
}