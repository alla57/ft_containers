#include <vector>
#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>
#include <memory>

int main()
{
	std::vector<int> v(12, 8);
	if (*v.begin())
		if (*v.begin() == 7)
		{
			std::cout << "one" << std::endl;
			std::cout << "two" << std::endl;
		}
		else
			std::cout << "three" << std::endl;
	else
		std::cout << "green" << std::endl;
	return (0);
}