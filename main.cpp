#include "algorithm.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "type_traits.hpp"
#include "utility.hpp"
#include "vector.hpp"

#include <map>
#include <vector>
#include <stack>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

void test_ft_vector_assign()
{
	ft::vector<int> vct(7);
	ft::vector<int> vct_two(4);
	ft::vector<int> vct_three;
	ft::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);
	vct_four.assign(6, 84);
	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);
}

void test_ft_vector_insert()
{
	ft::vector<int> vct(10);
	ft::vector<int> vct2;
	ft::vector<int> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	vct2.insert(vct2.end() - 2, 42);
	vct2.insert(vct2.end(), 2, 84);
	vct2.resize(4);
	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
}

void test_ft_vector_erase()
{
	ft::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	vct.erase(vct.begin() + 2);
	vct.erase(vct.begin());
	vct.erase(vct.end() - 1);
	vct.erase(vct.begin(), vct.begin() + 3);
	vct.erase(vct.end() - 3, vct.end() - 1);
	vct.push_back("Hello");
	vct.push_back("Hi there");
	vct.erase(vct.end() - 3, vct.end());
	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	vct.erase(vct.begin(), vct.end());
}

void test_ft_vector_push_pop()
{
	ft::vector<std::string> vct(8);
	ft::vector<std::string> vct2;
	ft::vector<std::string>::iterator it = vct.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);

	vct.push_back("One long string");
	vct2.push_back("Another long string");
	for (unsigned long int i = 0; i < 100; ++i)
		vct.push_back("AAAAAAAAAAAAAAA");
	for (unsigned long int i = 0; i < 100; ++i)
		vct2.push_back("BBBBBBBBBBBBBBBB");
	for (unsigned long int i = 0; i < 50; ++i)
		vct.pop_back();
	for (unsigned long int i = 0; i < 50; ++i)
		vct2.pop_back();
}

void test_ft_vector_oper()
{
	ft::vector<int> vct(1000, 8);

	for(unsigned int i = 0; i < vct.size() ; ++i)
		vct[i] = 5;
}

void test_std_vector_assign()
{
	std::vector<int> vct(7);
	std::vector<int> vct_two(4);
	std::vector<int> vct_three;
	std::vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);
	vct_four.assign(6, 84);
	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);
}

void test_std_vector_insert()
{
	std::vector<int> vct(10);
	std::vector<int> vct2;
	std::vector<int> vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	vct2.insert(vct2.end() - 2, 42);
	vct2.insert(vct2.end(), 2, 84);
	vct2.resize(4);
	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
}

void test_std_vector_erase()
{
	std::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	vct.erase(vct.begin() + 2);
	vct.erase(vct.begin());
	vct.erase(vct.end() - 1);
	vct.erase(vct.begin(), vct.begin() + 3);
	vct.erase(vct.end() - 3, vct.end() - 1);
	vct.push_back("Hello");
	vct.push_back("Hi there");
	vct.erase(vct.end() - 3, vct.end());
	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	vct.erase(vct.begin(), vct.end());
}

void test_std_vector_push_pop()
{
	std::vector<std::string> vct(8);
	std::vector<std::string> vct2;
	std::vector<std::string>::iterator it = vct.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);

	vct.push_back("One long string");
	vct2.push_back("Another long string");
	for (unsigned long int i = 0; i < 100; ++i)
		vct.push_back("AAAAAAAAAAAAAAA");
	for (unsigned long int i = 0; i < 100; ++i)
		vct2.push_back("BBBBBBBBBBBBBBBB");
	for (unsigned long int i = 0; i < 50; ++i)
		vct.pop_back();
	for (unsigned long int i = 0; i < 50; ++i)
		vct2.pop_back();
}

void test_std_vector_oper()
{
	std::vector<int> vct(1000, 8);

	for(unsigned int i = 0; i < vct.size() ; ++i)
		vct[i] = 5;
}

void test_ft_map_insert()
{
	ft::map<int, std::string> mp;
	ft::map<int, std::string> mp2;
	ft::map<int, std::string>::iterator it;
	std::stringstream buf;

	for (unsigned int i = 0; i < 1000; ++i)
	{
		buf.str("");
		buf << i;
		mp.insert(ft::pair<int, std::string>(i, buf.str()));
	}
	for (unsigned int i = 1000; i > 0; --i)
	{
		buf.str("");
		buf << i;
		mp2.insert(ft::pair<int, std::string>(i, buf.str()));
	}
	it = mp.begin();
	for (unsigned int i = 0; i < 50; ++i)
		++it;
	for (unsigned int i = 5000; i < 6000; ++i)
	{
		buf.str("");
		buf << i;
		mp.insert(it, ft::pair<int, std::string>(i, buf.str()));
	}
	it = mp.begin();
	for (unsigned int i = 0; i < 1000; ++i)
		++it;
	mp2.insert(it, mp.end());
}

void test_ft_map_erase(ft::map<int, std::string>& mp)
{
	for (unsigned int i = 0; i < 2999; ++i)
		mp.erase(mp.begin());
}

void test_std_map_insert()
{
	std::map<int, std::string> mp;
	std::map<int, std::string> mp2;
	std::map<int, std::string>::iterator it;
	std::stringstream buf;

	for (unsigned int i = 0; i < 1000; ++i)
	{
		buf.str("");
		buf << i;
		mp.insert(std::pair<int, std::string>(i, buf.str()));
	}
	for (unsigned int i = 1000; i > 0; --i)
	{
		buf.str("");
		buf << i;
		mp2.insert(std::pair<int, std::string>(i, buf.str()));
	}
	it = mp.begin();
	for (unsigned int i = 0; i < 50; ++i)
		++it;
	for (unsigned int i = 5000; i < 6000; ++i)
	{
		buf.str("");
		buf << i;
		mp.insert(it, std::pair<int, std::string>(i, buf.str()));
	}
	it = mp.begin();
	for (unsigned int i = 0; i < 1000; ++i)
		++it;
	mp2.insert(it, mp.end());
}

void test_std_map_erase(std::map<int, std::string>& mp)
{
	for (unsigned int i = 0; i < 2999; ++i)
		mp.erase(mp.begin());
}

int main()
{
	clock_t start, end;

	std::cout << "STD VECTOR TESTS ASSIGN" << std::endl;
	start = clock();
	test_std_vector_assign();
	end = clock();
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl;

	std::cout << "FT VECTOR TESTS ASSIGN" << std::endl;
	start = clock();
	test_ft_vector_assign();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;
	
	std::cout << "STD VECTOR TESTS INSERT" << std::endl;
	start = clock();
	test_std_vector_insert();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl;

	std::cout << "FT VECTOR TESTS INSERT" << std::endl;
	start = clock();
	test_ft_vector_insert();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;

	std::cout << "STD VECTOR TESTS ERASE" << std::endl;
	start = clock();
	test_std_vector_erase();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl;

	std::cout << "FT VECTOR TESTS ERASE" << std::endl;
	start = clock();
	test_ft_vector_erase();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;

	std::cout << "STD VECTOR TESTS PUSH_POP" << std::endl;
	start = clock();
	test_std_vector_push_pop();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl;

	std::cout << "FT VECTOR TESTS PUSH_POP" << std::endl;
	start = clock();
	test_ft_vector_push_pop();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;

	std::cout << "STD VECTOR TESTS OPERATOR[]" << std::endl;
	start = clock();
	test_std_vector_oper();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl;

	std::cout << "FT VECTOR TESTS OPERATOR[]" << std::endl;
	start = clock();
	test_ft_vector_oper();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;

	std::cout << "STD MAP TESTS INSERT" << std::endl;
	start = clock();
	test_std_map_insert();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl;

	std::cout << "FT MAP TESTS INSERT" << std::endl;
	start = clock();
	test_ft_map_insert();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;
	
	std::cout << "STD MAP TESTS ERASE" << std::endl;
	std::map<int, std::string> mp;
	std::stringstream buf;
	for (unsigned int i = 0; i < 3000; ++i)
	{
		buf.str("");
		buf << i;
		mp.insert(std::pair<int, std::string>(i, buf.str()));
	}
	start = clock();
	test_std_map_erase(mp);
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl;

	std::cout << "FT MAP TESTS ERASE" << std::endl;
	ft::map<int, std::string> mp2;
	for (unsigned int i = 0; i < 3000; ++i)
	{
		buf.str("");
		buf << i;
		mp2.insert(ft::pair<int, std::string>(i, buf.str()));
	}
	start = clock();
	test_ft_map_erase(mp2);
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;
	return 0;
}
