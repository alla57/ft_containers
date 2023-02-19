#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>
// #include <type_traits>

#include "type_traits.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "vector.hpp"

int main()
{
	ft::vector<int> v(5);
	ft::vector<int>::reverse_iterator rit(v.rbegin());
	ft::vector<int>::reverse_iterator rit2(v.rend());
	for (;rit != rit2; ++rit)
		std::cout << "non" << std::endl;
	return (0);
}