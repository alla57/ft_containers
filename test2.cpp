#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>
// #include <type_traits>
#include <map>
#include <list>

// #include "type_traits.hpp"
// #include "iterator.hpp"
// #include "utility.hpp"
// #include "vector.hpp"
// #include "stack.hpp"
#include "RBTree.hpp"
#include "map.hpp"

#include <functional>
#define T1 int
#define T2 std::string
#define TESTED_NAMESPACE ft
typedef TESTED_NAMESPACE::pair<const T1, T2> T3;
#include <sstream>
int main()
{
	std::stringstream s;
	unsigned int i = 25;
	s << i;
	std::cout << s.str() << std::endl;
	i = 28;
	s.str("");
	s << i;
	std::cout << s.str() << std::endl;
	// std::list<T3> lst;
	// unsigned int lst_size = 10;
	// for (unsigned int i = 0; i < lst_size; ++i)
	// 	lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	// TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());

	// TESTED_NAMESPACE::map<int, int> mp_range(it, --(--ite));
	// for (int i = 0; it != ite; ++it)
	// 	it->second = ++i * 5;

	// it = mp.begin(); ite = --(--mp.end());
	// TESTED_NAMESPACE::map<T1, T2> mp_copy(mp);
	// for (int i = 0; it != ite; ++it)
	// 	it->second = ++i * 7;

	// std::cout << "\t-- PART ONE --" << std::endl;
	// printSize(mp);
	// std::cout << "max_size = " << mp.max_size() << std::endl;

	// --it;
	// tree.insert(ft::pair<int, std::string>(24, "24"));
	// tree.insert(ft::pair<int, std::string>(38, "38"));
	// tree.insert(ft::pair<int, std::string>(1, "1"));
	// tree.insert(ft::pair<int, std::string>(12, "12"));
	// it = tree.begin();
	// tree.insert(ft::pair<int, std::string>(42, "42"));
	// tree.insert(ft::pair<int, std::string>(32, "32"));
	// tree.insert(ft::pair<int, std::string>(28, "28"));
	// tree.insert(ft::pair<int, std::string>(19, "19"));
	// tree.insert(ft::pair<int, std::string>(35, "35"));
	// tree.insert(ft::pair<int, std::string>(3, "3"));
	// tree.insert(ft::pair<int, std::string>(22, "22"));
	// tree.insert(ft::pair<int, std::string>(15, "15"));
	// tree.insert(ft::pair<int, std::string>(47, "47"));
	// tree.insert(ft::pair<int, std::string>(20, "20"));
	// tree.insert(ft::pair<int, std::string>(89, "89"));
	// tree.insert(ft::pair<int, std::string>(10, "10"));
	// tree.insert(ft::pair<int, std::string>(54, "54"));
	// tree.insert(ft::pair<int, std::string>(69, "69"));
	// tree.insert(ft::pair<int, std::string>(73, "73"));
	// tree.insert(ft::pair<int, std::string>(56, "56"));
	// tree.insert(ft::pair<int, std::string>(94, "94"));
	// tree.insert(ft::pair<int, std::string>(91, "91"));
	// tree.insert(ft::pair<int, std::string>(92, "92"));
	// tree.insert(ft::pair<int, std::string>(93, "93"));
	// it = tree.begin();
	// while (it != tree.end())
	// {
	// 	std::cout << "it = " << it->second << std::endl;
	// 	++it;
	// }
	// std::cout << std::endl;
	// for (it = tree.begin(); it != tree.end(); ++it)
	// {
	// 	if (it->first == 24)
	// 		{std::cout << "prout main" << std::endl; tree.erase(it);}
	// }
	// it = tree.begin();
	// while (it != tree.end())
	// {
	// 	std::cout << "it = " << it->second << std::endl;
	// 	++it;
	// }
	return(0);
}