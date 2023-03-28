#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <functional>
# include <memory>
# include <exception>
# include <algorithm>

# include "utility.hpp"
# include "iterator.hpp"
# include <iterator>

# define BLACK 1
# define RED 0

namespace ft
{
	//	RED-BLACK TREE NODE CLASS
	template <typename Val>
	class RB_Node
	{
	public:
		typedef RB_Node*					node_ptr;
		typedef typename Val::second_type	data_type;
		typedef typename Val::first_type	key_type;
		typedef Val							value_type;

		// RB_Node() : color(BLACK), left(NULL), right(NULL), parent(NULL), key(){}
		RB_Node(const value_type& value = value_type()) : value(value), color(RED), left(NULL), right(NULL), parent(NULL), key(value.first), is_nil(false){}

		const RB_Node& operator=(const RB_Node& other) {
			if (this == &other)
				return (*this);
			color = other.color;
			left = other.left;
			right = other.right;
			parent = other.parent;
			key = other.key;
			value = other.value;
			return (*this);
		}
		value_type	value;
		bool		color;
		node_ptr	left;
		node_ptr	right;
		node_ptr	parent;
		key_type	key;
		bool		is_nil;
		node_ptr	minimum(){
			node_ptr x = this;
			while (!(x->left->is_nil))
				x = x->left;
			return (x);
		}
		node_ptr	maximum(){
			node_ptr x = this;
			while (!(x->right->is_nil))
				x = x->right;
			return x;
		}
	};
	//	INCREMENT AND DECREMENT NODE
	template<typename Val>
	RB_Node<Val>*	rb_tree_increment(RB_Node<Val>* x){
		if (x->parent == NULL)
			return (x);
		if (!(x->right->is_nil))
			return x->right->minimum();
		// std::cout << "prout" << std::endl;
		RB_Node<Val>* y = x->parent;
		while (x == y->right)
		{
			x = y;
			y = y->parent;
		}
		if (x->right != y)
			x = y;
		return x;
	}
	template<typename Val>
	const RB_Node<Val>*	rb_tree_increment(const RB_Node<Val>* x){
		if (x->parent == NULL)
			return (x);
		if (!(x->right->is_nil))
			return x->right->minimum();
		// std::cout << "prout" << std::endl;
		RB_Node<Val>* y = x->parent;
		while (x == y->right)
		{
			x = y;
			y = y->parent;
		}
		if (x->right != y)
			x = y;
		return x;
	}

	template<typename Val>
	RB_Node<Val>* rb_tree_decrement(RB_Node<Val>* x){
		if (x->parent == NULL || (x->parent->parent == x && x->color == RED))
			return (x->right);
		if (!(x->left->is_nil))
			return x->left->maximum();
		RB_Node<Val>* y = x->parent;
		while (x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
	template<typename Val>
	const RB_Node<Val>* rb_tree_decrement(const RB_Node<Val>* x){
		if (x->parent == NULL || (x->parent->parent == x && x->color == RED))
			return (x->right);
		if (!(x->left->is_nil))
			return x->left->maximum();
		RB_Node<Val>* y = x->parent;
		while (x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	//	RED-BLACK TREE ITERATOR
	template<typename T>
	class RB_Iterator
	{
	public:
		typedef T											value_type;
		typedef T&											reference;
		typedef T*											pointer;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef std::ptrdiff_t								difference_type;
		typedef RB_Node<value_type>							node_type;
		typedef node_type*									node_ptr;

		node_ptr	node;

		RB_Iterator() : node() {}
		RB_Iterator(node_ptr other) : node(other) {}

		reference operator*() const {return (node->value);}
		pointer operator->() const {return(&(node->value));}
		RB_Iterator& operator++(){node = rb_tree_increment(node); return *this;}
		RB_Iterator operator++(int){RB_Iterator tmp(node); node = rb_tree_increment(node); return(tmp);}
		RB_Iterator& operator--(){node = rb_tree_decrement(node); return *this;}
		RB_Iterator operator--(int){RB_Iterator tmp(node); node = rb_tree_decrement(node); return(tmp);}
		friend bool operator==(const RB_Iterator& lhs, const RB_Iterator& rhs){return lhs.node == rhs.node;}
		friend bool operator!=(const RB_Iterator& lhs, const RB_Iterator& rhs){return !(lhs.node == rhs.node);}
	};

	template<typename T>
	class RB_Const_Iterator
	{
	public:
		typedef T											value_type;
		typedef const T&									reference;
		typedef const T*									pointer;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef std::ptrdiff_t								difference_type;
		typedef RB_Node<value_type>							node_type;
		typedef const node_type*							node_ptr;

		node_ptr	node;

		RB_Const_Iterator() : node() {}
		RB_Const_Iterator(node_ptr other) : node(other) {}
		RB_Const_Iterator(const RB_Iterator<value_type>& it) : node(it.node) {}

		reference operator*() const {return (node->value);}
		pointer operator->() const {return(&(node->value));}
		RB_Const_Iterator& operator++(){node = rb_tree_increment(node); return *this;}
		RB_Const_Iterator operator++(int){RB_Const_Iterator tmp(node); node = rb_tree_increment(node); return(tmp);}
		RB_Const_Iterator& operator--(){node = rb_tree_decrement(node); return *this;}
		RB_Const_Iterator operator--(int){RB_Const_Iterator tmp(node); node = rb_tree_decrement(node); return(tmp);}
		friend bool operator==(const RB_Const_Iterator& lhs, const RB_Const_Iterator& rhs){return lhs.node == rhs.node;}
		friend bool operator!=(const RB_Const_Iterator& lhs, const RB_Const_Iterator& rhs){return !(lhs.node == rhs.node);}
	};

	//	RED-BLACK TREE CLASS
	template< typename Key, typename Val, typename Compare = std::less<Key>, typename Allocator = std::allocator<Val>, typename Node = RB_Node<Val> >
	class RBTree
	{
	public:
		typedef Node													node_type;
		typedef typename Node::node_ptr									node_ptr;
		typedef Key														key_type;
		typedef typename Val::second_type								data_type;
		// typedef ft::pair<const Key, Data>							value_type;
		typedef Val														value_type;
		typedef Compare													key_compare;
		typedef Allocator												allocator_type;
		typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;
		typedef RB_Iterator<value_type>									iterator;
		typedef RB_Const_Iterator<value_type>							const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef std::size_t												size_type;

		node_ptr	Root;
		node_ptr	Nil;
		node_ptr	Header;
		size_type	count;

		//		CONSTRUCTORS
		// RBTree(const allocator_type& alloc = allocator_type()) : _node_allocator(alloc), _key_comp(){
		// 	_init_tree();
		// }
		RBTree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _node_allocator(alloc), _key_comp(comp){
			_init_tree();
		}
		template<typename InputIt>
		RBTree(InputIt first, InputIt last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _node_allocator(alloc), _key_comp(comp){
			_init_tree();
			range_insert(first, last);
		}
		RBTree(const RBTree& other) : _node_allocator(other._node_allocator), _key_comp(other._key_comp){
			if (this == &other)
				return;
			_init_tree();
			*this = other;
		}

		//		DESTRUCTOR
		~RBTree() {
			range_erase(begin(), end());
			_delete_header_and_nil();
		}

		//		ASSIGNEMENT OPERATOR
		RBTree& operator=(const RBTree& rhs){
			if (this == &rhs)
				return (*this);
			range_erase(begin(), end());
			_key_comp = rhs._key_comp;
			range_insert(rhs.begin(), rhs.end());
			return (*this);
		}
		//		ITERATORS
		iterator				begin(){return iterator(Header->left);}
		const_iterator			begin() const {return const_iterator(Header->left);}
		iterator				end(){return iterator(Header);}
		const_iterator			end() const {return const_iterator(Header);}

		//		MODIFIERS
		ft::pair<iterator, bool> insert(const value_type& value){
			bool not_found = search(value.first) == Nil;
			if (not_found)
			{
				_insert(value);
				_update_header();
				_update_root_parent();
				++count;
			}
			return ft::pair<iterator, bool>(iterator(search(value.first)), not_found);
		}
		template<typename InputIt>
		void range_insert(InputIt first, InputIt last){
			for (;first != last; ++first)
				insert(*first);
		}
		size_type	erase(const key_type& key){
			iterator pos(search(key));
			if (pos.node == Nil)
				return 0;
			erase(pos);			
			return 1;
		}
		iterator	erase(iterator& pos){
			iterator it(pos.node);
			++it;
			_delete_node(pos.node->key);
			_update_header();
			_update_root_parent();
			_node_allocator.destroy(pos.node);
			_node_allocator.deallocate(pos.node, 1);
			--count;
			return (it);
		}
		iterator	range_erase(iterator first, iterator last){
			iterator it;
			for(; first != last; first = it)
				it = erase(first);
			return (it);
		}
		void swap(RBTree& other){
			std::swap(Nil, other.Nil);
			std::swap(Header, other.Header);
			// std::swap(Header->parent, other.Header->parent);
			// std::swap(Header->left, other.Header->left);
			// std::swap(Header->right, other.Header->right);
			std::swap(Root, other.Root);
			// std::swap(Root->parent, other.Root->parent);
			std::swap(count, other.count);
			std::swap(_node_allocator, other._node_allocator);
			std::swap(_key_comp, other._key_comp);
		}
		//		ELEMENT ACCESS
		data_type&	at( const key_type& key ) {
			node_ptr tmp = search(key);
			if (tmp == Nil)
				throw(std::out_of_range("The value you're looking for is unavailable"));
			return tmp->value.second;
		}
		const data_type&	at( const key_type& key ) const {
			node_ptr tmp = search(key);
			if (tmp == Nil)
				throw(std::out_of_range("The value you're looking for is unavailable"));
			return tmp->value.second;
		}
		data_type&	operator[]( const key_type& key ) {
			node_ptr tmp = search(key);
			if (tmp == Nil)
				return insert(value_type(key, data_type())).first->second;
			return tmp->value.second;
		}
		node_allocator_type get_allocator() const {return _node_allocator;}
		size_type max_size() const {return _node_allocator.max_size();}
		node_ptr	search(const key_type& key) const {
			node_ptr x = Root;
			while (x != Nil && x != Header && _is_different(key, x->key))
			{
				if (_key_comp(key, x->key))
					x = x->left;
				else
					x = x->right;
			}
			return (x);
		}
		iterator	search_it(const key_type& key){
			node_ptr pos = search(key);
			if (pos == Nil)
				return end();
			return pos;
		}
		const_iterator	search_it(const key_type& key) const {
			node_ptr pos = search(key);
			if (pos == Nil)
				return end();
			return pos;
		}
		iterator lower_bound(const key_type& key){
			node_ptr x = Root;
			node_ptr y = Header;
			while (x != Nil)
			{
				if (_key_comp(x->key, key))
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return iterator(y);
		}
		const_iterator lower_bound(const key_type& key) const {
			node_ptr x = Root;
			node_ptr y = Header;
			while (x != Nil)
			{
				if (_key_comp(x->key, key))
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return const_iterator(y);
		}
		iterator upper_bound(const key_type& key){
			node_ptr x = Root;
			node_ptr y = Header;
			while (x != Nil)
			{
				if (!_key_comp(key, x->key))
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return iterator(y);
		}
		const_iterator upper_bound(const key_type& key) const {
			node_ptr x = Root;
			node_ptr y = Header;
			while (x != Nil)
			{
				if (!_key_comp(key, x->key))
					x = x->right;
				else
				{
					y = x;
					x = x->left;
				}
			}
			return const_iterator(y);
		}
	private:
		node_allocator_type	_node_allocator;
		key_compare			_key_comp;

		void	_init_tree(){
			_initialize_nil();
			Root = Nil;
			_initialize_header();
			count = 0;
		}
		void	_initialize_nil(){
			Nil = _create_node();
			Nil->color = BLACK;
			Nil->parent = NULL;
			Nil->is_nil = true;
		}

		void	_initialize_header(){
			Header = _create_node();
			Header->color = RED;
			Header->right = Header;
			Header->left = Header;
			Header->parent = NULL;
		}
		bool _is_different(const key_type& lhs,  const key_type& rhs) const {
			return _key_comp(lhs, rhs) || _key_comp(rhs, lhs);
		}
		void	_rotate_left(node_ptr x){
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != Nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == Header)// x->parent == NULL
				Root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		void	_rotate_right(node_ptr x){
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != Nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == Header)
				Root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		void	_transplant(node_ptr u, node_ptr v){
			if (u->parent == NULL || u->parent == Header) // (u->parent == NULL)
				Root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			// if (v != Nil)
			v->parent = u->parent;
		}
		void	_delete_node(const key_type& key){
			node_ptr z = search(key);
			if (z == Nil || z == Header) // (z == Nil)
				return ;
			node_ptr y = z;
			bool y_origine_color = y->color;
			node_ptr x;
			// node_ptr xp;
			if (z->left == Nil)
			{
				x = z->right;
				_transplant(z, z->right);
			}
			else if (z->right == Nil)
			{
				x = z->left;
				_transplant(z, z->left);
			}
			else
			{
				y = z->right->minimum();
				y_origine_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			// if (z->key == 73 && x->parent == z->parent)
			// 	std::cout << "prout" << std::endl;
			if (y_origine_color == BLACK)
				_deleteFix(x);
		}
		void	_deleteFix(node_ptr x){
			node_ptr w;
			while (x != Root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						_rotate_left(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							_rotate_right(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						_rotate_left(x->parent);
						x = Root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						_rotate_right(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->left->color == BLACK)
						{
							w->right->color = BLACK;
							w->color = RED;
							_rotate_left(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						_rotate_right(x->parent);
						x = Root;
					}
				}
			}
			x->color = BLACK;
		}

		node_ptr	_create_node(const value_type& value = value_type()){
			node_ptr node = _node_allocator.allocate(1);
			_node_allocator.construct(node, value);
			return (node);
		}

		void	_insert(const value_type& value){
			node_ptr z =  _create_node(value);
			z->left = Nil;
			z->right = Nil;
			node_ptr y = NULL;
			node_ptr x = Root;

			while (x != Nil)
			{
				y = x;
				if (_key_comp(z->key, x->key))
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == NULL)
				Root = z;
			else if (_key_comp(z->key, y->key))
				y->left = z;
			else
				y->right = z;
			_insert_fix(z);
		}
		void _insert_fix(node_ptr z) {
			node_ptr y;
			while (z->parent != NULL && z->parent->color == RED)
			{
				if (z->parent == z->parent->parent->left)
				{
					y = z->parent->parent->right;
					if (y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->right)
						{
							z = z->parent;
							_rotate_left(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						_rotate_right(z->parent->parent);
					}
				}
				else
				{
					y = z->parent->parent->left;
					if (y->color == RED)
					{
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							_rotate_right(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						_rotate_left(z->parent->parent);
					}
				}
				if (z == Root)
					break;
			}
			Root->color = BLACK;
		}

		void	_update_header(){
			if (Root == Nil)
			{
				Header->parent = NULL;
				Header->left = Header;
				Header->right = Header;
			}
			else
			{
				Header->parent = Root;
				Header->left = Root->minimum();
				Header->right = Root->maximum();
			}
		}

		void	_update_root_parent(){
			Root->parent = Header;
		}

		void	_delete_header_and_nil(){
			_node_allocator.destroy(Header);
			_node_allocator.deallocate(Header, 1);
			_node_allocator.destroy(Nil);
			_node_allocator.deallocate(Nil, 1);
		}
	};
}

#endif