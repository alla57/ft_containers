#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "type_traits.hpp"
#include <iterator>

namespace ft
{
	//									ITERATOR_TRAITS
	template<class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef	typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef	T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef	T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	// 									ITERATOR CATEGORY
	template<typename Iter>
	typename ft::iterator_traits<Iter>::iterator_category iterator_category(const Iter&){
		return typename ft::iterator_traits<Iter>::iterator_category();
	}

	//									ITERATOR
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	// 									DISTANCE
	template<typename It>
	typename iterator_traits<It>::difference_type	do_distance(It first, It last, std::random_access_iterator_tag){
		return (last - first);
	}
	template<typename It>
	typename iterator_traits<It>::difference_type	do_distance(It first, It last, std::input_iterator_tag){
		typename iterator_traits<It>::difference_type count = 0;
		for(; first != last; ++first)
			++count;
		return count;
	}
	template<typename InputIt>
	typename iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last){
		return do_distance(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
	}

	//									REVERSE_ITERATOR
	template<class Iter>
	class reverse_iterator : public iterator	<typename iterator_traits<Iter>::iterator_category,
												typename iterator_traits<Iter>::value_type,
												typename iterator_traits<Iter>::difference_type,
												typename iterator_traits<Iter>::pointer,
												typename iterator_traits<Iter>::reference>
	{
	protected:
		//		Member Objects
		Iter current;
	public:
		//		Member Types
		typedef Iter											iterator_type;
		typedef typename iterator_traits<Iter>::difference_type	difference_type;
		typedef typename iterator_traits<Iter>::reference		reference;
		typedef typename iterator_traits<Iter>::pointer			pointer;

		//		Constructors
		reverse_iterator() : current(){}
		explicit reverse_iterator(iterator_type x) : current(x){}
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other) : current(other.base()){}

		//		Assignement Operator Overload
		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other){current = other.base(); return (*this);}

		//		Member functions
		iterator_type base() const {return(current);}

		//		Operator Overloads
		reference operator*() const {iterator_type tmp = current; return *--tmp;}
		pointer operator->() const {return &(operator*());}
		reference operator[](difference_type n) const {return(current[-n - 1]);}
		reverse_iterator& operator++(){--current; return(*this);}
		reverse_iterator& operator--(){++current; return(*this);}
		reverse_iterator operator++(int){reverse_iterator tmp = *this; --current; return (tmp);}
		reverse_iterator operator--(int){reverse_iterator tmp = *this; ++current; return (tmp);}
		reverse_iterator operator+(difference_type n) const {return (reverse_iterator(current - n));}
		reverse_iterator operator-(difference_type n) const {return (reverse_iterator(current + n));}
		reverse_iterator& operator+=(difference_type n) {current -= n; return (*this);}
		reverse_iterator& operator-=(difference_type n) {current += n; return (*this);}
	};
	//		reverse_iterator Non Members Functions
	template<class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs){
		return (lhs.base() == rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs){
		return (lhs.base() != rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator< (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs){
		return (lhs.base() > rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs){
		return (lhs.base() >= rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator> (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs){
		return (lhs.base() < rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs){
		return (lhs.base() <= rhs.base());
	}
	template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it){
		return (reverse_iterator<Iter>(it.base() - n));
	}
	// template<class Iter>
	// typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs){
	// 	return (rhs.base() - lhs.base());
	// }
	template< class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ){
		return (rhs.base() - lhs.base());
	}

	// 									NORMAL_ITERATOR
	template<class Iter>
	class normal_iterator
	{
	protected:
		// 		Member Objects
		Iter current;
	public:
		// 		Member Types
		typedef Iter												iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::difference_type 	difference_type;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::pointer				pointer;

		// 		Constructors
		normal_iterator() : current(Iter()){}
		normal_iterator(const Iter& i) : current(i){}
		// template<typename U>
		// normal_iterator(const typename ft::enable_if< ft::is_same<U, Iter>::value, normal_iterator<U> >::type & i) : current(i.base()){}
		template <class U>
		normal_iterator(const normal_iterator<U>& other) : current(other.base()){}

		//		Assignement Operator Overload
		template<class U>
		normal_iterator& operator=(const normal_iterator<U> & i){current = i.base(); return (*this);}

		//		Member functions
		const Iter& base() const {return (current);}

		//		Operator Overloads
		reference operator*() const {return (*current);}
		pointer operator->() const {return current;}
		normal_iterator& operator++(){++current; return (*this);}
		normal_iterator operator++(int){return (normal_iterator(current++));}
		normal_iterator& operator--(){--current; return (*this);}
		normal_iterator operator--(int){return (normal_iterator(current--));}
		reference operator[](difference_type n) const {return current[n];}
		normal_iterator& operator+=(difference_type n) {current += n; return (*this);}
		normal_iterator operator+(difference_type n) const {return normal_iterator(current + n);}
		normal_iterator& operator-=(difference_type n) {current -= n; return (*this);}
		normal_iterator operator-(difference_type n) const {return normal_iterator(current - n);}
	};
	//		normal_iterator Non Members Functions
	template<typename IteratorL, typename IteratorR>
	bool operator==(const ft::normal_iterator<IteratorL>& lhs, const ft::normal_iterator<IteratorR>& rhs){
		return (lhs.base() == rhs.base());
	}
	template<typename Iterator>
    bool operator==(const ft::normal_iterator<Iterator>& lhs, const ft::normal_iterator<Iterator>& rhs){
		return (lhs.base() == rhs.base());
	}
	template<typename IteratorL, typename IteratorR>
	bool operator!=(const ft::normal_iterator<IteratorL>& lhs, const ft::normal_iterator<IteratorR>& rhs){
		return (lhs.base() != rhs.base());
	}
	template<typename Iterator>
	bool operator!=(const ft::normal_iterator<Iterator>& lhs, const ft::normal_iterator<Iterator>& rhs){
		return (lhs.base() != rhs.base());
	}
	// Random access iterator requirements
	template<typename IteratorL, typename IteratorR>
	bool operator<(const ft::normal_iterator<IteratorL>& lhs, const ft::normal_iterator<IteratorR>& rhs){
		return (lhs.base() < rhs.base());
	}
	template<typename Iterator>
	bool operator<(const ft::normal_iterator<Iterator>& lhs, const ft::normal_iterator<Iterator>& rhs){
		return (lhs.base() < rhs.base());
	}
	template<typename IteratorL, typename IteratorR>
	bool operator>(const ft::normal_iterator<IteratorL>& lhs, const ft::normal_iterator<IteratorR>& rhs){
		return (lhs.base() > rhs.base());
	}
	template<typename Iterator>
	bool operator>(const ft::normal_iterator<Iterator>& lhs, const ft::normal_iterator<Iterator>& rhs){
		return (lhs.base() > rhs.base());
	}
	template<typename IteratorL, typename IteratorR>
	bool operator<=(const ft::normal_iterator<IteratorL>& lhs, const ft::normal_iterator<IteratorR>& rhs){
		return (lhs.base() <= rhs.base());
	}
	template<typename Iterator>
	bool operator<=(const ft::normal_iterator<Iterator>& lhs, const ft::normal_iterator<Iterator>& rhs){
		return (lhs.base() <= rhs.base());
	}
	template<typename IteratorL, typename IteratorR>
	bool operator>=(const ft::normal_iterator<IteratorL>& lhs, const ft::normal_iterator<IteratorR>& rhs){
		return (lhs.base() >= rhs.base());
	}
	template<typename Iterator>
	bool operator>=(const ft::normal_iterator<Iterator>& lhs, const ft::normal_iterator<Iterator>& rhs){
		return (lhs.base() >= rhs.base());
	}
	template<typename IteratorL, typename IteratorR>
	typename ft::normal_iterator<IteratorL>::difference_type operator-(const ft::normal_iterator<IteratorL>& lhs, const ft::normal_iterator<IteratorR>& rhs){
		return (lhs.base() - rhs.base());
	}
	template<typename Iterator>
	typename ft::normal_iterator<Iterator>::difference_type operator-(const ft::normal_iterator<Iterator>& lhs, const ft::normal_iterator<Iterator>& rhs){
		return (lhs.base() - rhs.base());
	}
	template<typename Iterator>
	ft::normal_iterator<Iterator> operator+(typename ft::normal_iterator<Iterator>::difference_type n, const ft::normal_iterator<Iterator>& i){
		return (ft::normal_iterator<Iterator>(i.base() + n));
	}
}

#endif