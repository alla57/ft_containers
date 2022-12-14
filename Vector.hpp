#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <exception>
#include <iostream>

namespace ft
{

	template< class T, class Allocator = std::allocator<T> >
	class Vector
	{
	public :
	//		MEMBER TYPES
		typedef T							value_type;
		typedef Allocator					allocator_type;
		typedef std::size_t					size_type;
		typedef std::ptrdiff_t				difference_type;
		typedef value_type&					reference;
		typedef const value_type&			const_reference;
		typedef	Allocator::pointer			pointer;
		typedef Allocator::const_pointer	const_pointer;
		// typedef ft::Iterator				iterator;
		// typedef	ft::const_iterator			const_iterator;
		// typedef	ft::reverse_iterator<iterator>		reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	//		CONSTRUCTORS
		explicit Vector(const Allocator& alloc = Allocator());
		explicit Vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator());
		template<class InputIt>
		Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
		Vector(const Vector& other);

	//		DESTRUCTOR
		~Vector();

	//		ASSIGNEMENT OPERATOR OVERLOAD
		Vector& operator=(const Vector& other);

	//		MEMBER FUNCTIONS
		void assign(size_type count, const T& value);
		template<class InputIt>
		void assign(InputIt first, InputIt last);
		allocator_type get_allocator() const; // std:: ????

	//		ELEMENT ACCESS
		reference at( size_type pos );
		const_reference at( size_type pos ) const;
		reference operator[]( size_type pos );
		const_reference operator[]( size_type pos ) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		T* data();
		const T* data() const;

	//		ITERATORS
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

	//		CAPACITY
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void reserve( size_type new_cap );
		size_type capacity() const;

	//		MODIFIERS
		void clear();
		iterator insert( const_iterator pos, const T& value );
		iterator insert( const_iterator pos, size_type count, const T& value );
		template< class InputIt >
		iterator insert( const_iterator pos, InputIt first, InputIt last );
		iterator erase( iterator pos );
		iterator erase( iterator first, iterator last );
		void push_back( const T& value );
		void pop_back();
		void resize( size_type count, T value = T() );
		void swap( vector& other );

	private :
	}

	//		NON-MEMBER FUNCTIONS
	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs );
	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs );
}

//		CONSTRUCTORS DEFINITION

template<class T, class Allocator = std::allocator<T> >
Vector<T, Allocator>::Vector(const Allocator& alloc)
{
}


#endif