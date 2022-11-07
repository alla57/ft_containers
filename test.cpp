#include <vector>
#include <iostream>

using namespace std;

template <typename T>
struct ParameterTraits {
	template <typename PT, bool byValOrByRef> struct ParameterTraitsImpl;

	template <typename PT>
	struct ParameterTraitsImpl<PT, true> {
		typedef PT Type;
	};

	template <typename PT>
	struct ParameterTraitsImpl<PT, false> {
		typedef const PT & Type;
	};
	typedef typename ParameterTraitsImpl<T, (sizeof(T) < sizeof(void *))>::Type ParameterType;
};

template <typename T>
T mini(typename ParameterTraits<T>::ParameterType first, typename ParameterTraits<T>::ParameterType second)
{
	return (first < second ? first : second);
}

int main()
{
	std::vector<int>* a = new std::vector<int>;
	(void)a;
	delete a;
	return (0);
}