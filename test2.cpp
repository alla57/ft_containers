#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include "test.h"


// #include "Iterator.hpp"
// int main()
// {
// 	std::vector<int> v(10, 8);
// 	v.clear()
// 	// std::cout << v.capacity() << std::endl;
// 	int arr[] = {1, 2, 3, 4};
// 	ft::normal_iterator<int*> it;
// 	it = arr;
// 	std::__is_integer< ft::normal_iterator<int*> >::__type _Integral;
// 	std::cout << _Integral.value << std::endl;
// 	return (0);
// }
#include <limits>
#include "TypeTraits.hpp"
int main()
{
	std::vector<int> v(25, 8);
	std::vector<int> u(25, 5);
	// std::vector<int>::iterator itFirst(v.begin());
	// std::vector<int>::iterator itLast(u.at(5));
	v.insert(v.end(), u.begin(), u.begin() + 5);//v.end(), u.begin(), u.begin() + 5
	std::cout << v.at(29) << std::endl;
	// v.reserve()
	return (0);
}

// return (std::min)(__diffmax, __allocmax);
// there is two parenthesis here, the first one is a function call, the second one is a function call