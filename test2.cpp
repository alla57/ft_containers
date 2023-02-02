#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>

int main()
{
	std::allocator<int> alloc;
	std::allocator<int>::pointer first = alloc.allocate(5);
	std::uninitialized_fill(first, first + 5, 3);
	std::cout << *first << std::endl;
	return (0);
}