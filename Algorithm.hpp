#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	//			EQUAL
	template<class InputIT1, class InputIT2>
	bool equal(InputIT1 first1, InputIT1 last2, InputIT2 first1, InputIT2 last2);

	template<class InputIT1, class InputIT2, class BinaryPredicate>
	bool equal(InputIT1 first1, InputIT1 last1, InputIT2 first2, BinaryPredicate pred);
}

#endif