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
#include <chrono>

void test_ft_vector()
{
	// assign
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
	// insert
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
	// erase
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
	// push and pop back
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
}
 
void test_std_vector()
{
	// assign
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
	// insert
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
	// erase
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
}

int main()
{
	clock_t start, end;

	std::cout << "FT VECTOR TESTS" << std::endl;
	start = clock();
	test_std_vector();
	end = clock();
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;

	std::cout << "STD VECTOR TESTS" << std::endl;
	start = clock();
	test_std_vector();
	end = clock();
	time_taken = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time taken by program is : " << std::fixed << time_taken * 1000 << std::setprecision(5);
	std::cout << " ms" << std::endl << std::endl;
	return 0;
}
