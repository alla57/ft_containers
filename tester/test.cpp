#include <vector>
#include <iostream>
#include <stdint.h>

#include <iterator>
#include <type_traits>
#include <utility>
#include <algorithm>

#include "../Iterator.hpp"
#include "../TypeTraits.hpp"
#include "../Utility.hpp"
#include "../Algorithm.hpp"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

template <class T>
bool	iterator_traitsCheck(T iterator){
	if (!std::is_same<typename std::iterator_traits<T>::difference_type, typename T::difference_type>::value)
		return (false);
	if (!std::is_same<typename std::iterator_traits<T>::value_type, typename T::value_type>::value)
		return (false);
	if (!std::is_same<typename std::iterator_traits<T>::pointer, typename T::pointer>::value)
		return (false);
	return (true);
}

// template <>
// bool	iteratorTraitsCheck<T*>(T a){
// 	if (std::iterator_traits<T>::difference_type)
// }

// template <>
// bool	iteratorTraitsCheck(T a){
// 	if (std::iterator_traits<const T*>::difference_type)
// }

TEST_CASE("Iterator tests", "[factorial]"){
	std::vector<int>::iterator it;
	SECTION("Checking iterator_traits using std::vector iterator"){
	CHECK(iterator_traitsCheck(it));
	}
}

// unsigned int Factorial( unsigned int number ) {
//     return number <= 1 ? number : Factorial(number-1)*number;
// }

// TEST_CASE( "Factorials are computed", "[factorial]" ) {
//     REQUIRE( Factorial(1) == 1 );
//     REQUIRE( Factorial(2) == 3 );
//     REQUIRE( Factorial(3) == 6 );
//     REQUIRE( Factorial(10) == 3628800 );
// }
