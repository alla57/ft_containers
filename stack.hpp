#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
		
		explicit stack (const container_type& ctnr = container_type()) : _container(ctnr){}

		//	ELEMENT ACCESS
		reference top() {return _container.back();}
		const_reference top() const {return _container.back();}

		//	CAPACITY
		bool empty() const {return size() == 0;}
		size_type size() const {return _container.size();}

		//	MODIFIERS
		void push(const value_type& value) {_container.push_back(value);}
		void pop() {_container.pop_back();}

	protected:
		container_type _container;

	private:
		template<typename Tp, typename Cont>
		friend bool operator==(const stack<Tp, Cont>&, const stack<Tp, Cont>&);

		template<typename Tp, typename Cont>
		friend bool operator<(const stack<Tp, Cont>&, const stack<Tp, Cont>&);
	};
	//	NON-MEMBER FUNCTIONS
	template< class T, class Container >
	bool operator==( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ){return lhs._container == rhs._container;}
	template< class T, class Container >
	bool operator!=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ){return !(lhs == rhs);}
	template< class T, class Container >
	bool operator< ( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ){return lhs._container < rhs._container;}
	template< class T, class Container >
	bool operator<=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ){return (lhs < rhs || lhs == rhs);}
	template< class T, class Container >
	bool operator> ( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ){return !(lhs <= rhs);}
	template< class T, class Container >
	bool operator>=( const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs ){return !(lhs < rhs);}
}

#endif