#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <functional>
# include <memory>

# include "utility.hpp"

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
		RB_Node(const value_type& value) : color(RED), left(NULL), right(NULL), parent(NULL), key(value.first), data(value.second){}

		const RB_Node& operator=(const RB_Node& other) {
			if (this == &other)
				return (*this);
			color = other.color;
			left = other.left;
			right = other.right;
			parent = other.parent;
			key = other.key;
			data = other.data;
		}
		node_ptr	parent;
		node_ptr	left;
		node_ptr	right;
		const key_type	key;
		data_type	data;
		bool		color;
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

		RBTree(const allocator_type& alloc = allocator_type()) : Root(), _node_allocator(alloc){
			_initialize_nil();
			Root = Nil;
		}
		node_ptr	Root;
		node_ptr	Nil;

		node_ptr	grandParent(node_ptr z) {return z->parent->parent;}
		node_ptr	aunt(node_ptr z){
			node_ptr zGrandParent = z->parent->parent;
			if (zGrandParent->left == z->parent)
				return z->GrandParent->right;
			return z->GrandParent->left;
		}
		void	color_flip(node_ptr z){
			node_ptr zGrandParent = grandParent(z);
			node_ptr zAunt = aunt(z);
			if (z->parent != NULL)//modify if we put Nil as parent of Root
				z->parent->color = !z->parent->color;
			if (zGrandParent != NULL)//modify if we put Nil as parent of Root
				zGrandParent->color = !zGrandParent->color;
			if (zAunt != Nil)
				zAunt->color = !zAunt->color;
		}
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
		void	insert(const value_type& value){
			node_ptr z =  _create_node(value);
			node_ptr y = Nil;
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
			if (y == Nil)
				Root = z;
			else if (z->key < y->key)
				y->left = z;
			else
				y->right = z;
			z->left = Nil;
			z->right = Nil;
			// if (z->parent->parent == nullptr) {
			// 	return;
			// }
			insert_fix(z);
		}

		void insertFix(node_ptr z) {
		node_ptr y;
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
			// if (z == root)
			// {
			// 	break;
			// }
		}
		Root->color = BLACK;
		}
	private:
		node_allocator_type	_node_allocator;

		void	_initialize_nil(){
			Nil = _create_node();
			Nil->color = BLACK;
			Nil->parent = Nil;
		}

		node_ptr	_create_node(const value_type& value = value_type()){
			node_ptr node = _node_allocator.allocate(1);
			_node_allocator.construct(node, value);// if doesnt compile node_type(value)
			return (node);
		}
	};
}

#endif