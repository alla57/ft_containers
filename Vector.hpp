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
			_start = _allocate_and_initialize(count, value);
			_end_of_storage = _start + count;
			_finish = _end_of_storage;
		}
		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) : _allocator(alloc){
			if (typename ft::is_integral<InputIt>)
				{
					_start = _allocate_and_initialize(static_cast<size_type>(first), static_cast<value_type>(last));
					_end_of_storage = _start + static_cast<size_type>(first);
					_finish = _end_of_storage;
				}
			else
				_range_initialize(first, last);
		}
		vector(const vector& other){*this = other;}

	//		DESTRUCTOR
		~vector();

	//		ASSIGNEMENT OPERATOR OVERLOAD
		vector& operator=(const vector& other);

	//		MEMBER FUNCTIONS
		void assign(size_type count, const T& value){
			clear();
			
		}
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
		iterator begin() {return iterator(_start);}
		const_iterator begin() const {return const_iterator(_start);}
		iterator end() {return iterator(_finish);}
		const_iterator end() const {return const_iterator(_finish);}
		reverse_iterator rbegin() {return reverse_iterator(begin());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(begin());}
		reverse_iterator rend() {return reverse_iterator(end());}
		const_reverse_iterator rend() const {return const_reverse_iterator(end());}

	//		CAPACITY
		bool empty() const {return (_start == _finish);}
		size_type size() const {return (_finish - _start);}
		size_type max_size() const {return _allocator.max_size();}
		void reserve( size_type new_cap ) {
			if (new_cap < this->capacity())
				return ;
			pointer tmp_start = _allocate(new_cap);
			size_type old_size = size();
			std::uninitialized_copy(_start, _finish, tmp_start);
			_range_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = tmp_start;
			_end_of_storage = _start + new_cap;
			_finish = _start + old_size;
		}
		size_type capacity() const {return (_end_of_storage - _start);}

	//		MODIFIERS
		void clear(){
			_range_destroy(_start, _finish);
			_finish = _start;
		}
		iterator insert( const_iterator pos, const T& value ){
			const size_type pos_index = pos - begin();
			if (_finish != _end_of_storage)
				_insert(pos.base(), value);
			else
				_realloc_and_insert_n(pos.base(), 1, value);
			return iterator(_start + pos_index);
		}
		iterator insert( const_iterator pos, size_type count, const T& value ){
			if (count == 0)
				return (pos);
			_fill_insert(pos, count, value);
			return iterator(_start);
		}
		template< class InputIt >
		iterator insert( const_iterator pos, InputIt first, InputIt last ){
			if (typename ft::is_integral<InputIt>)
				return insert(pos, static_cast<size_type>(first), static_cast<value_type>(last));
			else
			{
				if (first == last)
					return pos;
				_range_insert(pos, first.base(), last.base());
			}
			return iterator(_start);
		}

		iterator erase( iterator pos ){
			_erase();
		}
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
		size_type _check_length(size_type n_elm_to_add) const{
			if (max_size() - size() < n_elm_to_add)
				throw(std::length_error("cannot create std::vector larger than max_size()"));
			const size_type length = size() + std::max(size(), n_elm_to_add);
			if (length < size() || length > max_size())
				return (max_size());
			return (length);
      }
		// optimizable if we add a specialization of forward iterator
		// maybe it should throw if error in push_back process
		template<class InputIt>
		void	_range_initialize(InputIt first, InputIt last){
			for (; first != last; ++first)
			{
				push_back(*first);
			}
		}
		pointer	_allocate(size_type count){
			if (count > _allocator.max_size())
				throw(std::length_error("cannot create std::vector larger than max_size()"));
			pointer storage_start = _allocator.allocate(count);
			return (storage_start);
		}
		void	_deallocate(pointer start, std::size_t count){
			alloc.deallocate(start, count);
		}
		pointer	_allocate_and_initialize(size_type count, const value_type& value){
			pointer storage_start = _allocate(count);
			std::uninitialized_fill(storage_start, storage_start + count, value);
			return (storage_start);
		}
		void	_range_destroy(pointer first, pointer last){
			for (; first != last; ++first)
				_allocator.destroy(first);
		}
		void	_construct(pointer pos, const value_type& value){
			_allocator.construct(pos, value);
		}
		void	_insert(pointer pos, const value_type& value){
			if (pos == _finish)
				_construct(_finish++, value);
			else
			{
				_construct(_finish, *(_finish - 1));
				++_finish;
				std::copy_backward(iterator(pos), iterator(_finish - 2), _finish);
				*pos = value;
			}
		}
		void	_realloc_and_insert_n(pointer pos, const size_type count, const value_type& value)
		{
			size_type new_capacity = _check_length(count);
			pointer tmp_start = _allocate(new_capacity);
			size_type old_size = size();
			size_type pos_index = pos - _start;
			std::uninitialized_copy(_start, pos, tmp_start);
			std::uninitialized_fill_n(tmp_start + pos_index, count, value);
			std::uninitialized_copy(pos, _finish, tmp_start + pos_index + count);
			_range_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = tmp_start;
			_end_of_storage = _start + new_capacity;
			_finish = _start + old_size + count;
		}
		void	_fill_insert(pointer pos, const size_type count, const value_type& value) {
			if (count == 0)
				return ;
			size_type available_storage = _end_of_storage - _finish;
			size_type elm_until_end = _finish - pos;
			if (count <= available_storage)
			{
				if (count <= elm_until_end)
				{
					std::uninitialized_copy(_finish - count, _finish, _finish);
					std::copy_backward(pos, _finish - count, _finish);
					std::fill_n(pos, count, value);
				}
				else
				{
					std::uninitialized_copy(pos, _finish, pos + count);
					std::fill_n(pos, elm_until_end, value);
					std::uninitialized_fill_n(_finish, count - elm_until_end, value);
				}
				_finish += count;
			}
			else
				_realloc_and_insert_n(pos, count, value);
		}
		void	_range_realloc_and_insert(pointer pos, pointer first, pointer last){
			size_type count = last - first;
			size_type new_capacity = _check_length(count);
			pointer tmp_start = _allocate(new_capacity);
			size_type old_size = size();
			size_type pos_index = pos - _start;
			std::uninitialized_copy(_start, pos, tmp_start);
			std::uninitialized_copy(first, last, tmp_start + pos_index);
			std::uninitialized_copy(pos, _finish, tmp_start + pos_index + count);
			_range_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = tmp_start;
			_end_of_storage = _start + new_capacity;
			_finish = _start + old_size + count;
		}
		void	_range_insert(pointer pos, pointer first, pointer last){
			if (first == last)
				return ;
			size_type available_storage = _end_of_storage - _finish;
			size_type elm_until_end = _finish - pos;
			size_type count = last - first;
			if (count <= available_storage)
			{
				if (count <= elm_until_end)
				{
					std::uninitialized_copy(_finish - count, _finish, _finish);
					std::copy_backward(pos, _finish - count, _finish);
					std::copy(first, last, pos);
				}
				else
				{
					std::uninitialized_copy(pos, _finish, pos + count);
					std::copy(first, first + elm_until_end, pos);
					std::uninitialized_copy(first + elm_until_end, last, _finish);
				}
				_finish += count;
			}
			else
				_range_realloc_and_insert(pos, first, last);
		}
		void	_erase(pointer pos)
		{
			if ()
		}
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