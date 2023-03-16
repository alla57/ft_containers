#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <exception>
# include <iostream>

# include "utility.hpp"
# include "iterator.hpp"
# include "RBTree.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef ft::pair<const Key, T>										value_type;
		typedef std::size_t													size_type;
		typedef std::ptrdiff_t												difference_type;
		typedef Compare														key_compare;
		typedef Allocator													allocator_type;
		typedef value_type&													reference;
		typedef const value_type&											const_reference;
		typedef typename Allocator::pointer									pointer;
		typedef typename Allocator::const_pointer							const_pointer;
		typedef RBTree<key_type, value_type, key_compare, allocator_type>	rb_tree_type;
		typedef typename rb_tree_type::iterator								iterator;
		typedef typename rb_tree_type::const_iterator						const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		class value_compare
		{
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type& x, const value_type& y) const {return comp(x.first, y.first);}

		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
		};

		//		CONSTRUCTORS
		map() : tree(){}
		explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type()) : tree(comp, alloc) {}
		template<typename InputIt>
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(first, last, comp, alloc) {}
		map( const map& other ) : tree(other.tree){}

		//		DESTRUCTOR
		~map() {}
		//		ASSIGNEMENT OPERATOR
		map& operator=(const map& rhs){
			if (this == &rhs)
				return (*this);
		}
		//		MEMBER FUNCTION
		allocator_type get_allocator() const {return tree._node_allocator};
		//		ELEMENT ACCESS
		mapped_type&		at( const Key& key ) {return tree.at(key);}
		const mapped_type&	at( const Key& key ) const {return tree.at(key);}
		mapped_type&		operator[]( const Key& key ){return tree[key];}
		//		ITERATORS
		iterator				begin(){return tree.begin();}
		const_iterator			begin() const {return tree.begin();}
		iterator				end(){return tree.end();}
		const_iterator			end() const {return tree.end();}
		reverse_iterator		rbegin(){return reverse_iterator(end());}
		const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator		rend() {return reverse_iterator(begin());}
		const_reverse_iterator	rend() const {return const_reverse_iterator(begin());}
		//		CAPACITY
		bool		empty() const {return begin() == end();}
		size_type	size() const {return count;}
		size_type	max_size() const {return tree.max_size();}
		//		MODIFIERS
		void						clear(){tree.range_erase(begin(), end());}
		ft::pair<iterator, bool>	insert(const value_type& value){
			if (insert())
		}

	private:
		rb_tree_type tree;
	};
}
#endif