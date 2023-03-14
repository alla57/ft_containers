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
#include "RBTree.hpp"

int main()
{
	// ft::RBTree<int, std::string> tree;
	// tree.insert(ft::pair<int, std::string>(1, "one"));
	ft::stack<int> st;
	std::map<int, std::string> m;
	std::map<int, std::string>::iterator it;
	// m.insert(std::pair<int, std::string>(0 ,"aprout"));
	// m.insert(std::pair<int, std::string>(1 ,"one"));
	// m.insert(std::pair<int, std::string>(2 ,"two"));
	it = m.end();
	std::cout << "header = " << it._M_node << std::endl;
	std::cout << "header->right = " << it._M_node->_M_right << std::endl;
	std::cout << "header->left = " << it._M_node->_M_left << std::endl;
	std::cout << "header->parent = " << it._M_node->_M_parent << std::endl;
	it = m.begin();
	std::cout << "begin = " << it._M_node << std::endl;
	// --it;
	// std::cout << "begin - 1 = " << it->second << std::endl;
	// --it;
	// std::cout << "begin - 2 = " << it->second << std::endl;

	// std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	// m.insert(std::pair<int, std::string>(1 ,"btoto"));
	// ++it;
	// std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	// m.insert(std::pair<int, std::string>(2 ,"cyoyo"));
	// ++it;
	// std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	// m.insert(std::pair<int, std::string>(3 ,"dysl"));
	// ++it;
	// std::cout << "address = " << std::addressof(*it) << " - value = " << sizeof(*it) << std::endl;
	// std::cout << "address total = " << sizeof(m) << std::endl;
	return(0);
}