#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	//			EQUAL
	template<class InputIT1, class InputIT2>
	bool equal(InputIT1 first1, InputIT1 last1, InputIT2 first2, InputIT2 last2)
	{
		InputIT1 it1 = first1;
		InputIT2 it2 = first2;
		while (true)
		{
			if (*it1 != *it2)
				return (false);
			if (it1 == last1)
				break;
			++it1;
			++it2;
		}
		return (true);
	}
	template<class InputIT1, class InputIT2, class BinaryPredicate>
	bool equal(InputIT1 first1, InputIT1 last1, InputIT2 first2, BinaryPredicate pred)
	{
		InputIT1 i = first1;
		if (*i != *(first2 + (i - first1)) || pred(*i, *(first2 + (i - first1))) == false)
			return (false);
		++i;
		while (i != last1)
		{
			if (*i != *(first2 + (i - first1)) || pred(*i, *(first2 + (i - first1))) == false) // maybe only predicate condition to respect ???
				return (false);
			++i;
		}
		if (!pred(first1, last1))
			return (false);
		equal<InputIT1, InputIT2>(first1, last1, first2, InputIT2 last2)
	}
}

#endif