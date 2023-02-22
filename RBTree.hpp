#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <functional>
# include <memory>

# define BLACK 1
# define RED 0

namespace ft
{
	//	RED-BLACK TREE NODE CLASS
	template <typename Key, typename Data>
	class RB_Node
	{
	public:
		typedef RB_Node*		node_ptr;
		typedef Data		data_type;
		typedef Key			key_type;

		RB_Node() : color(RED), left(NULL), right(NULL), parent(NULL), key(), data(){}
		RB_Node(key_type& key, data_type& data) : color(RED), left(NULL), right(NULL), parent(NULL), key(key), data(data){}
		node_ptr	parent;
		node_ptr	left;
		node_ptr	right;
		key_type&	key;
		data_type&	data;
		bool		color;
	};

	//	RED-BLACK TREE CLASS
	template< typename Data, typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator<Data> >
	class RBTree
	{
	public:
		typedef typename RB_Node::node_ptr	node_ptr;
		typedef Data						data_type;
		typedef Key							key_type;
		typedef Compare						key_compare;
		typedef Allocator					allocator_type;

		RBTree(const allocator_type& alloc = allocator_type()) : Root(), Nil(){
			Nil->color = BLACK;
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
		void	insert(key_type key, data_type data){
			node_ptr z = new Node(key, data);
			node_ptr y = NULL;
			node_ptr x = Root;

			while (x != NULL)
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
			if (z->parent == NULL)
			{
				z->color = BLACK;
				return;
			}

			if (z->parent->parent == nullptr) {
				return;
			}
			insert_fix(z);
		}
	};
}

#endif