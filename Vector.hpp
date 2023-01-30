#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <exception>
#include <iostream>

#include "Iterator.hpp"

namespace ft
{

	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
	public :
	//		MEMBER TYPES
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef	typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef ft::normal_iterator<pointer>			iterator;
		typedef	ft::normal_iterator<const_pointer>		const_iterator;
		typedef	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	//		CONSTRUCTORS
		explicit vector(const Allocator& alloc = Allocator()) : _allocator(alloc){}
		explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) : _allocator(alloc){
			if (count > _allocator.max_size())
				throw(std::length_error("cannot create std::vector larger than max_size()"));
			_start = _allocator.allocate(count);
			_end_of_storage = _start + count;
			std::uninitialized_fill(_start, _end_of_storage, value);
		}
		// optimizable if we add a specialization of forward iterator
		// maybe it should throw if error in push_back process
		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) : _allocator(alloc){
			for (; first != last; ++first)
			{
				push_back(*first);
			}
		}
		vector(const vector& other);

	//		DESTRUCTOR
		~vector();

	//		ASSIGNEMENT OPERATOR OVERLOAD
		vector& operator=(const vector& other);

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
		allocator_type	_allocator;
		pointer			_start;
		pointer			_finish;
		pointer			_end_of_storage;

		size_type	_check_init_length()
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
Vector<T, Allocator>::Vector(const Allocator& alloc = Allocator())
{
}

#endif