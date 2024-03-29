#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <exception>
#include <iostream>
#include <algorithm>

#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"

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
		explicit vector(const Allocator& alloc = Allocator()) : _allocator(alloc), _start(), _finish(), _end_of_storage(){}
		explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type()) : _allocator(alloc){
			_start = _allocate_and_initialize(count, value);
			_end_of_storage = _start + count;
			_finish = _end_of_storage;
		}
		template<class InputIt>
vector(typename ft::enable_if<ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const Allocator& alloc = Allocator()) : _allocator(alloc) {
  _start = _allocate_and_initialize(static_cast<size_type>(first), static_cast<value_type>(last));
  _end_of_storage = _start + static_cast<size_type>(first);
  _finish = _end_of_storage;
}

template<class InputIt>
vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const Allocator& alloc = Allocator()) : _allocator(alloc) {
  difference_type count = ft::distance(first, last);
  _start = _allocate(count);
  _end_of_storage = _start + count;
  _finish = _start;
  _range_initialize(first, last);
}
		vector(const vector& other) : _allocator(), _start(), _finish(), _end_of_storage(){*this = other;}

	//		DESTRUCTOR
		~vector(){
			clear();
			_deallocate(_start, _end_of_storage - _start);
		}

	//		ASSIGNEMENT OPERATOR OVERLOAD
		vector& operator=(const vector& other) {
			if (this == &other)
				return (*this);
			assign(other.begin(), other.end());
			return (*this);
		}


	//		MEMBER FUNCTIONS
		void assign(size_type count, const T& value){
			clear();
			insert(_start, count, value);
		}

		template<class InputIt>
		void assign(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value, int>::type = 0){
			clear();
			insert(_start, first, last);
		}

		allocator_type get_allocator() const{
			return allocator_type();
		}


	//		ELEMENT ACCESS
		reference at( size_type pos ) {
			_check_range(pos);
			return ((*this)[pos]);
		}
		const_reference at( size_type pos ) const {
			_check_range(pos);
			return ((*this)[pos]);
		}
		reference operator[]( size_type pos ) {
			return *(_start + pos);
		}
		const_reference operator[]( size_type pos ) const{
			return *(_start + pos);
		}
		reference front() {
			return *(begin());
		}
		const_reference front() const {
			return *(begin());
		}
		reference back() {
			return *(end() - 1);
		}
		const_reference back() const {
			return *(end() - 1);
		}
		T* data() {
			return (_start);
		}
		const T* data() const {
			return (_start);
		}

	//		ITERATORS
		iterator begin() {return iterator(_start);}
		const_iterator begin() const {return const_iterator(_start);}
		iterator end() {return iterator(_finish);}
		const_iterator end() const {return const_iterator(_finish);}
		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

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
		iterator insert( iterator pos, const T& value ){
			const size_type pos_index = pos - begin();
			if (_finish != _end_of_storage)
				_insert(pos, value);
			else
				_realloc_and_insert_n(pos, 1, value);
			return (begin() + pos_index);
		}
		iterator insert( iterator pos, size_type count, const T& value ){
			if (count == 0)
				return (pos);
			_fill_insert(pos, count, value);
			return begin();
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last ){
			_insert_dispatch(pos, first, last, ft::is_integral<InputIt>());
		}
		iterator erase( iterator pos ){
			_range_erase(pos, pos + 1);
			return (pos);
		}

		iterator erase( iterator first, iterator last ){
			if (first != last)
				_range_erase(first, last);
			return (first);
		}

		void push_back( const T value ){
			insert(end(), value);
		}

		void pop_back(){
			erase(end() - 1);
		}

		void resize( size_type count, T value = T() ){
			if (count > size())
				insert(end(), count - size(), value);
			else
				erase(begin() + count, end());
		}
		void swap( vector& other ){
			if (this == &other)
				return;
			std::swap(_start, other._start);
			std::swap(_finish, other._finish);
			std::swap(_end_of_storage, other._end_of_storage);
		}

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
		template<class InputIt>
		void	_range_initialize(InputIt first, InputIt last/*, ft::true_type*/){
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
			_allocator.deallocate(start, count);
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
		void	_insert(iterator pos, const value_type& value){
			if (pos.base() == _finish)
				_construct(_finish++, value);
			else
			{
				_construct(_finish, *(_finish - 1));
				++_finish;
				std::copy_backward(pos, end() - 1, end());
				*pos = value;
			}
		}
		void	_realloc_and_insert_n(iterator pos, const size_type count, const value_type& value)
		{
			size_type new_capacity = _check_length(count);
			pointer tmp_start = _allocate(new_capacity);
			size_type old_size = size();
			size_type pos_index = pos - begin();
			std::uninitialized_copy(begin(), pos, tmp_start);
			std::uninitialized_fill_n(tmp_start + pos_index, count, value);
			std::uninitialized_copy(pos, end(), tmp_start + pos_index + count);
			_range_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = tmp_start;
			_end_of_storage = _start + new_capacity;
			_finish = _start + old_size + count;
		}
		void	_fill_insert(iterator pos, const size_type count, const value_type& value) {
			if (count == 0)
				return ;
			size_type available_storage = _end_of_storage - _finish;
			size_type elm_until_end = end() - pos;
			if (count <= available_storage)
			{
				if (count <= elm_until_end)
				{
					std::uninitialized_copy(_finish - count, _finish, _finish);
					std::copy_backward(pos, end() - count, _finish);
					std::fill_n(pos, count, value);
				}
				else
				{
					std::uninitialized_copy(pos, end(), pos + count);
					std::fill_n(pos, elm_until_end, value);
					std::uninitialized_fill_n(_finish, count - elm_until_end, value);
				}
				_finish += count;
			}
			else
				_realloc_and_insert_n(pos, count, value);
		}
		template<typename InputIt>
		void	_range_realloc_and_insert(iterator pos, InputIt first, InputIt last, std::input_iterator_tag){
			if (pos == end())
			{
				for (; first != last; ++first)
					insert(end(), *first);
			}
			else if (first != last)
			{
				vector tmp(first, last);
				insert(pos, begin(), end());
			}
		}
		template<typename ForwardIt>
		void	_range_realloc_and_insert(iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag){
			size_type count = ft::distance(first, last);
			size_type new_capacity = _check_length(count);
			pointer tmp_start = _allocate(new_capacity);
			size_type old_size = size();
			size_type pos_index = pos - begin();
			std::uninitialized_copy(begin(), pos, tmp_start);
			std::uninitialized_copy(first, last, tmp_start + pos_index);
			std::uninitialized_copy(pos, end(), tmp_start + pos_index + count);
			_range_destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);
			_start = tmp_start;
			_end_of_storage = _start + new_capacity;
			_finish = _start + old_size + count;
		}
		template<class InputIt>
		void	_range_insert(iterator pos, InputIt first, InputIt last){
			if (first == last)
				return ;
			size_type available_storage = _end_of_storage - _finish;
			size_type elm_until_end = end() - pos;
			size_type count = 0;
			for (InputIt tmp_it = first; tmp_it != last; ++tmp_it)
				++count;
			if (count <= available_storage)
			{
				if (count <= elm_until_end)
				{
					std::uninitialized_copy(_finish - count, _finish, _finish);
					std::copy_backward(pos, end() - count, _finish);
					std::copy(first, last, pos);
				}
				else
				{
					std::uninitialized_copy(pos, end(), pos + count);
					std::copy(first, first + elm_until_end, pos);
					std::uninitialized_copy(first + elm_until_end, last, _finish);
				}
				_finish += count;
			}
			else
				_range_realloc_and_insert(pos, first, last, typename ft::iterator_traits<InputIt>::iterator_category());
		}
		void	_range_erase(iterator first, iterator last)
		{
			size_type count = last - first;
			std::copy(last, end(), first);
			_range_destroy(_finish - count, _finish);
			_finish -= count;
		}
		void	_check_range(const size_type n) const
		{
			if (n >= size())
				throw (std::out_of_range("vector::_check_range: n is out of boundaries"));
		}
		template<typename Integral>
		void	_insert_dispatch(iterator pos, Integral first, Integral last, ft::true_type){
			insert(pos, static_cast<size_type>(first), static_cast<value_type>(last));
		}
		template<typename InputIt>
		void	_insert_dispatch(iterator pos, InputIt first, InputIt last, ft::false_type){
			if (first == last)
				return;
			vector tmp(first, last);
			_range_insert(pos, tmp.begin(), tmp.end());
		}
	};
	//								NON-MEMBER FUNCTIONS
	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return !(lhs == rhs);
	}
	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return (lhs < rhs || lhs == rhs);
	}
	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return !(lhs <= rhs);
	}
	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ){
		return !(lhs < rhs);
	}
	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ){
		return (lhs.swap(rhs));
	}
}
#endif