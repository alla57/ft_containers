#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

template<typename T, typename Allocator = std::allocator>
class Vector
{
public :
//		CONSTRUCTORS
	Vector();
	explicit Vector(const Allocator& alloc);
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
private :
}

#endif