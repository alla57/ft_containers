#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>

void	test(std::vector<int>::pointer& pone)
{
	++pone;
}

int main()
{
	std::vector<int> v(12, 8);
	std::vector<int>::pointer pone = &(*v.begin());
	test(pone);
	*pone = 3;
	std::cout << *v.begin() << std::endl;
	return (0);
}