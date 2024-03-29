#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <exception>
# include <iostream>

# include "utility.hpp"
# include "iterator.hpp"
# include "RBTree.hpp"
# include "algorithm.hpp"

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

			value_compare() : comp() {}
			bool operator()(const value_type& x, const value_type& y) const {return comp(x.first, y.first);}

		protected:
			key_compare comp;
			value_compare(key_compare c) : comp(c) {}
		};

		//		CONSTRUCTORS
		map() : tree(){}
		explicit map(const key_compare& comp, const allocator_type& alloc = allocator_type()) : tree(comp, alloc) {}
		template<typename InputIt>
		map(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : tree(comp, alloc) {insert(first, last);}
		map( const map& other ) : tree(other.tree){}

		//		DESTRUCTOR
		~map() {}
		//		ASSIGNEMENT OPERATOR
		map& operator=(const map& rhs){
			if (this == &rhs)
				return (*this);
			tree = rhs.tree;
			return *this;
		}
		//		MEMBER FUNCTION
		allocator_type get_allocator() const {return tree.get_allocator();}
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
		size_type	size() const {return tree.count;}
		size_type	max_size() const {return tree.max_size();}
		//		MODIFIERS
		void						clear(){tree.range_erase(begin(), end());}
		ft::pair<iterator, bool>	insert(const value_type& value){return tree.insert(value);}
		iterator					insert(iterator pos, const value_type& value){(void)pos; return insert(value).first;}
		template<class InputIt>
		void						insert(InputIt first, InputIt last){return tree.range_insert(first, last);}
		iterator					erase(iterator pos){iterator res(pos);++res;tree.erase(pos); return res;}
		iterator					erase(iterator first, iterator last){return tree.range_erase(first, last);}
		size_type					erase(const Key& key){return tree.erase(key);}
		void						swap(map& other){tree.swap(other.tree);}
		//		LOOKUP
		size_type									count(const Key& key) const {return tree.search(key) != tree.Nil;}
		iterator									find(const Key& key){return tree.search_it(key);}
		const_iterator								find(const Key& key) const {return tree.search_it(key);}
		iterator									lower_bound(const Key& key){return tree.lower_bound(key);}
		const_iterator								lower_bound(const Key& key) const {return tree.lower_bound(key);}
		iterator									upper_bound(const Key& key){return tree.upper_bound(key);}
		const_iterator								upper_bound(const Key& key) const {return tree.upper_bound(key);}
		ft::pair<iterator, iterator>				equal_range(const Key& key){return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));}
		ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const {return ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));}
		//		OBSERVERS
		key_compare		key_comp() const {return key_compare();}
		value_compare	value_comp() const {return value_compare();}

	private:
		rb_tree_type tree;
	};
	//		NON-MEMBER FUNCTIONS
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs ){lhs.swap(rhs);}
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
		return !(lhs == rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
		return lhs < rhs || lhs == rhs;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
		return (rhs < lhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs ){
		return !(lhs < rhs);
	}
}
#endif