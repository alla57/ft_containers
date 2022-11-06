#include <vector>
#include <iostream>

int main()
{
	std::vector<int>* a = new std::vector<int>;
	(void)a;
	delete a;
	// (void)b;
	// std::cout << sizeof(a) << std::endl;
	// std::vector<int> b;
	// b.push_back(25);
	// b.push_back(25);
	// b.push_back(25);
	// std::cout << b.capacity() << std::endl;
	return (0);
}