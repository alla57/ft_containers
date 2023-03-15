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

#include <functional>

int main()
{
	ft::RBTree<int, ft::pair<const int, std::string> >  tree;
	ft::RBTree<int, ft::pair<const int, std::string> >::iterator it;
	it = tree.begin();
	// ft::stack<int> st;
	// std::map<int, std::string> m;
	// std::map<int, std::string>::iterator it;
	// m.insert(std::pair<int, std::string>(0 ,"aprout"));
	// m.insert(std::pair<int, std::string>(1 ,"one"));
	// m.insert(std::pair<int, std::string>(2 ,"two"));

	// --it;
	tree.insert(ft::pair<int, std::string>(24, "24"));
	tree.insert(ft::pair<int, std::string>(38, "38"));
	tree.insert(ft::pair<int, std::string>(1, "1"));
	tree.insert(ft::pair<int, std::string>(12, "12"));
	tree.insert(ft::pair<int, std::string>(42, "42"));
	tree.insert(ft::pair<int, std::string>(32, "32"));
	tree.insert(ft::pair<int, std::string>(28, "28"));
	tree.insert(ft::pair<int, std::string>(19, "19"));
	tree.insert(ft::pair<int, std::string>(35, "35"));
	tree.insert(ft::pair<int, std::string>(3, "3"));
	tree.insert(ft::pair<int, std::string>(22, "22"));
	tree.insert(ft::pair<int, std::string>(15, "15"));
	tree.insert(ft::pair<int, std::string>(47, "47"));
	tree.insert(ft::pair<int, std::string>(20, "20"));
	tree.insert(ft::pair<int, std::string>(89, "89"));
	tree.insert(ft::pair<int, std::string>(10, "10"));
	tree.insert(ft::pair<int, std::string>(54, "54"));
	tree.insert(ft::pair<int, std::string>(69, "69"));
	tree.insert(ft::pair<int, std::string>(73, "73"));
	tree.insert(ft::pair<int, std::string>(56, "56"));
	tree.insert(ft::pair<int, std::string>(94, "94"));
	tree.insert(ft::pair<int, std::string>(91, "91"));
	tree.insert(ft::pair<int, std::string>(92, "92"));
	tree.insert(ft::pair<int, std::string>(93, "93"));
	it = tree.begin();
	while (it != tree.end())
	{
		std::cout << "it = " << it->second << std::endl;
		++it;
	}
	std::cout << std::endl;
	for (it = tree.begin(); it != tree.end(); ++it)
	{
		if (it->first == 73)
			{std::cout << "prout" << std::endl; tree.erase(it);}
	}
	it = tree.begin();
	while (it != tree.end())
	{
		std::cout << "it = " << it->second << std::endl;
		++it;
	}
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