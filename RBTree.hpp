#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <functional>

# define BLACK 1
# define RED 0

template< typename Data, typename Key, typename Compare = std::less<Key> >
class RBTree
{
public:
	typedef Data	data_type;
	typedef Key		key_type;

	RBTree() : Root(), Nil(){
		Nil->color = BLACK;
	}
// pour l'instant pas nil. On garde les NULL et si besoin on changera
	// class Node;
	class Node
	{
	public:
		Node() : color(RED), left(NULL), right(NULL), parent(NULL), key(), data(){}
		Node(key_type& key, data_type& data) : color(RED), left(NULL), right(NULL), parent(NULL), key(key), data(data){}
		Node*		parent;
		Node*		left;
		Node*		right;
		key_type	key;
		data_type	data;
		bool		color;
	};
	Node*	Root;
	Node*	Nil;

	Node*	grandParent(Node* z) {return z->parent->parent;}
	Node*	aunt(Node* z){
		Node* zGrandParent = z->parent->parent;
		if (zGrandParent->left == z->parent)
			return z->GrandParent->right;
		return z->GrandParent->left;
	}
	void	color_flip(Node* z){
		Node* zGrandParent = grandParent(z);
		Node* zAunt = aunt(z);
		if (z->parent != NULL)//modify if we put Nil as parent of Root
			z->parent->color = !z->parent->color;
		if (zGrandParent != NULL)//modify if we put Nil as parent of Root
			zGrandParent->color = !zGrandParent->color;
		if (zAunt != Nil)
			zAunt->color = !zAunt->color;
	}
	void	rotate_left(Node* x){
		Node* xNewParent = x->right;
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
	void	rotate_right(Node* x){
		Node* xNewParent = x->left;
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
		Node* z = new Node(key, data);
		Node* y = NULL;
		Node* x = Root;

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

#endif