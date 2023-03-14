#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <functional>
# include <memory>

# include "utility.hpp"
# include <iterator>

# define BLACK 1
# define RED 0

namespace ft
{
	//	RED-BLACK TREE NODE CLASS
	template <typename Key, typename Data>
	class RB_Node
	{
	public:
		typedef RB_Node*			node_ptr;
		typedef Data				data_type;
		typedef Key					key_type;
		typedef ft::pair<Key, Data> value_type;

		// RB_Node() : color(BLACK), left(NULL), right(NULL), parent(NULL), key(){}
		RB_Node(const value_type& value = value_type()) : value(value), color(RED), left(NULL), right(NULL), parent(NULL), key(value.first){}

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
		node_ptr	parent;
		node_ptr	left;
		node_ptr	right;
		key_type	key;
		value_type	value;
		bool		color;
	};
	//	INCREMENT AND DECREMENT NODE
	template<typename Key, typename Data>
	RB_Node<Key, Data>*	rb_tree_increment(RB_Node<Key, Data>* x){
		// if (x->right == NULL)
		// 	return x;
		if (x->right->right != NULL)
			return minimum(x->right);
		RB_Node<Key, Data>* y = x->parent;
		while (x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	template<typename Key, typename Data>
	RB_Node<Key, Data>* rb_tree_decrement(RB_Node<Key, Data>* x){
		if (x->left->left != NULL)
			return maximum(x->left);
		RB_Node<Key, Data>* y = x->parent;
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
		typedef RB_Node<typename T::T1, typename T::T2>		node_type;
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

	//	RED-BLACK TREE CLASS
	template< typename Key, typename Data, typename Node = RB_Node<Key, Data>, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, Data> > >
	class RBTree
	{
	public:
		typedef Node													node_type;
		typedef typename Node::node_ptr									node_ptr;
		typedef Data													data_type;
		typedef Key														key_type;
		typedef ft::pair<const Key, Data>								value_type;
		typedef Compare													key_compare;
		typedef Allocator												allocator_type;
		typedef typename Allocator::template rebind<node_type>::other	node_allocator_type;
		typedef RB_Iterator												iterator;

		RBTree(const allocator_type& alloc = allocator_type()) : _node_allocator(alloc){
			_initialize_nil();
			Root = Nil;
			_initialize_header();
		}
		node_ptr	Root;
		node_ptr	Nil;
		node_ptr	Header;

		// node_ptr	grandParent(node_ptr z) {return z->parent->parent;}
		// node_ptr	aunt(node_ptr z){
		// 	node_ptr zGrandParent = z->parent->parent;
		// 	if (zGrandParent->left == z->parent)
		// 		return z->GrandParent->right;
		// 	return z->GrandParent->left;
		// }
		iterator	begin(){return iterator(Header->left);}
		iterator	end(){return iterator(Header);}
		void	rotate_left(node_ptr x){
			node_ptr xNewParent = x->right;
			x->right = xNewParent->left;
			if (xNewParent->left != NULL)
				xNewParent->left->parent = x;
			xNewParent->parent = x->parent;
			if (x->parent == NULL)
				Root = xNewParent;
			else if (x == x->parent->left)
				x->parent->left = xNewParent;
			else
				x->parent->right = xNewParent;
			xNewParent->left = x;
			x->parent = xNewParent;
		}
		void	rotate_right(node_ptr x){
			node_ptr xNewParent = x->left;
			x->left = xNewParent->right;
			if (xNewParent->right != NULL)
				xNewParent->right->parent = x;
			xNewParent->parent = x->parent;
			if (x->parent == NULL)
				Root = xNewParent;
			else if (x == x->parent->right)
				x->parent->right = xNewParent;
			else
				x->parent->left = xNewParent;
			xNewParent->right = x;
			x->parent = xNewParent;
		}
		void insert(const value_type& value){
			if (search(value.first) != Nil)
				return ;
			_insert(value);
			_update_header();
			_update_root_parent();
		}
		node_ptr	search(const key_type& key){
			node_ptr x = Root;
			while (x != Nil && x->key != key)
			{
				if (key < x->key)
					x = x->left;
				else
					x = x->right;
			}
			return (x);
		}
		node_ptr	minimum(node_ptr x){
			while (x->left != Nil)
				x = x->left;
			return (x);
		}
		node_ptr	maximum(node_ptr x){
			while (x->right != Nil)
				x = x->right;
			return x;
		}
		void	transplant(node_ptr u, node_ptr v){
			if (u->parent == NULL)
				Root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}
		void	delete_node(key_type& key){
			node_ptr z = search(key);
			if (z == Nil)
				return ;
			node_ptr y = z;
			bool y_origine_color = y->color;
			node_ptr x;
			if (z->left == Nil)
			{
				x = z->right;
				transplant(z, z->right);
			}
			else if (z->right == Nil)
			{
				x = z->left;
				transplant(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				y_origine_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (y_origine_color == BLACK)
				deleteFix(x);
		}
		void	deleteFix(node_ptr x){
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
						rotate_left(x->parent);
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
							rotate_right(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						rotate_left(x->parent);
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
						rotate_right(x->parent);
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
							rotate_left(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rotate_right(x->parent);
						x = Root;
					}
				}
			}
			x->color = BLACK;
		}
	private:
		node_allocator_type	_node_allocator;

		void	_initialize_nil(){
			Nil = _create_node();
			Nil->color = BLACK;
			Nil->parent = NULL;
		}

		void	_initialize_header(){
			Header = _create_node();
			Header->color = BLACK;
			Header->right = Header;
			Header->left = Header;
			Header->parent = NULL;
		}

		node_ptr	_create_node(const value_type& value = value_type()){
			node_ptr node = _node_allocator.allocate(1);
			_node_allocator.construct(node, node_type(value));// if doesnt compile node_type(value)
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
				if (z->key < x->key)
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == NULL)
				Root = z;
			else if (z->key < y->key)
				y->left = z;
			else
				y->right = z;
			insert_fix(z);
		}
		void _insert_fix(node_ptr z) {
			node_ptr y;
			// if segfault its because when z is root (at first insert) z->parent->color should segfault
			while (z->parent->color == RED)
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
							rotate_left(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotate_right(z->parent->parent);
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
							rotate_right(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rotate_left(z->parent->parent);
					}
				}
				if (z == Root)
					break;
			}
			Root->color = BLACK;
		}

		void	_update_header(){
			Header->parent = Root;
			Header->left = minimum(Root);
			Header->right = maximum(Root);
		}

		void	_update_root_parent(){
			Root->parent = Header;
		}
	};
}

#endif