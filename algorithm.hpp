#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	//			EQUAL
	template<class InputIT1, class InputIT2>
	bool equal(InputIT1 first1, InputIT1 last1, InputIT2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}
	template<class InputIT1, class InputIT2, class BinaryPredicate>
	bool equal(InputIT1 first1, InputIT1 last1, InputIT2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	// 			LEXICOGRAPHCAL COMPARE
	template <class InputIT1, class InputIT2>
	bool lexicographical_compare(InputIT1 first1, InputIT1 last1, InputIT2 first2, InputIT2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
	template <class InputIT1, class InputIT2, class Compare>
	bool lexicographical_compare(InputIT1 first1, InputIT1 last1, InputIT2 first2, InputIT2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}
}

#endif