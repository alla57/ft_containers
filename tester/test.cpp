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
bool	iteratorTraitsCheck(T a){
	if (std::iterator_traits<T>::difference_type != T::difference_type)
		return (false);
	if (std::iterator_traits<T>::value_type != T::value_type)
		return (false);
	if (std::iterator_traits<T>::pointer != T::pointer)
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
	CHECK((iteratorTraitsCheck(std::vector<int>::iterator)));
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
