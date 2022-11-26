#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		//	Member Types
		typedef T1	first_type;
		typedef T2	second_type;
		//	Member Variables
		T1 first;
		T2 second;
		//	Constructors
		pair(): first(), second(){}
		template <class U1, class U2>
		pair(const pair<U1, U2>& pr): first(pr.first), second(pr.second){}
		pair(const T1& a, const T2& b): first(a), second(b){}
		//	Assignement Operator Overload
		pair & operator=(const pair& pr) {first = pr.first; second = pr.second; return (*this);}
	};
	//	Non-Member functions
		//	Make Pair
	template <class T1, class T2>
	ft::pair<T1, T2>	make_pair(T1 a, T2 b){return (pair<T1, T2>(a, b));}
	//	Comparison Operator Overload
	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return ((lhs.first == rhs.first) && (lhs.second == rhs.second));}
	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){return (!(lhs == rhs));}
	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ){
		if (lhs.first < rhs.first)
			return (true);
		else if (rhs.first < lhs.first)
			return (false);
		else if (lhs.second < rhs.second)
			return (true);
		return (false);
	}
	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return (!(rhs < lhs));}
	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return (rhs < lhs);}
	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {return (!(lhs < rhs));}
}

#endif