#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include "test.h"


#include "Iterator.hpp"
int main()
{
	// std::vector<int> v(10, 8);
	// std::cout << v.capacity() << std::endl;
	int arr[] = {1, 2, 3, 4};
	ft::normal_iterator<int*> it;
	it = arr;
	std::__is_integer< ft::normal_iterator<int*> >::__type _Integral;
	std::cout << _Integral.value << std::endl;
	// std::__throw_length_error(__N("cannot create std::vector larger than max_size()"));
	// throw(std::length_error("cannot create std::vector larger than max_size()"));
	return (0);
}