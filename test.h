#include <iostream>
#include <string>

class two
	{
	public:
		two(){
			std::cout << "i am two" << std::endl;
		}
	};

class one : public 
{
public:
	one(){
		std::cout << "i am one" << std::endl;
	}
};