#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>
// #include <type_traits>
#include <map>

#include "type_traits.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "stack.hpp"

int main()
{
	ft::stack<int> st;
	std::map<int, std::string> m;
	std::map<int, std::string>::iterator it;
	m.insert(std::pair<int, std::string>(0 ,"aprout"));
	it = m.begin();
	std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	m.insert(std::pair<int, std::string>(1 ,"btoto"));
	++it;
	std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	m.insert(std::pair<int, std::string>(2 ,"cyoyo"));
	++it;
	std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	m.insert(std::pair<int, std::string>(3 ,"dysl"));
	++it;
	std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	std::cout << "address total = " << sizeof(m) << std::endl;
	return(0);
}