#include <vector>
#include <iostream>

using namespace std;

template<typename T>
struct ParameterTraits
{
	template <typename PT, bool ByValOrByRef> struct ParameterTraitsImpl;
	
	template <typename PT>
	struct ParameterTraitsImpl<PT, true>
	{
		typedef PT	type;
	};

	template <typename PT>
	struct ParameterTraitsImpl<PT, false>
	{
		typedef PT&	type;
	};

	typedef typename ParameterTraitsImpl< T, (sizeof(T) < sizeof(T&))>::type	ParameterType;
};

template<typename T>
T min(typename ParameterTraits<T>::ParameterType first, typename ParameterTraits<T>::ParameterType last)
{
	std::cout << sizeof(first) << std::endl;
	std::cout << sizeof(last) << std::endl;
	return (first);
}

int main()
{
	char a = 'a';
	char b = 'b';
	min<char>(a, b);
	return (0);
}