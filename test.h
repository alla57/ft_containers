#include <iostream>
#include <string>

#include <memory>
#include <utility>

template <typename Key, typename Data>
class node_test
{
public:
	typedef std::pair<const Key, Data> data_type;
	node_test(): n(42){
		// std::cout << "i am two" << std::endl;
		n = new OBJECT();
	}
	data_type* data_address(){
		return (&value);
	}
	void	print_data(){
		std::cout << "Key = " << value.first << " Value = " << value.second << std::endl;
	}
	data_type value;
	OBJECT* n;
};

template<typename Key, typename Data, typename Allocator>
class rb_tree_test
{
public:
	typedef node_test<Key, Data>		node_type;
	typedef Allocator					data_allocator_type;
	typedef std::pair<const Key, Data>	data_type;
	typedef typename Allocator::template rebind<node_type>::other node_allocator;

	rb_tree_test(data_allocator_type& alloc = data_allocator_type()) : _alloc_node(), _alloc_data(alloc){}
	void create_node(const data_type& value){
		node_p = _alloc_node.allocate(1); // malloc
		_alloc_node.construct(node_p);
		_alloc_data.construct(node_p->data_address(), value);
	}
	void	print_node(){
		node_p->print_data();
	}
	node_type*		node_p;
private:
	node_allocator _alloc_node;
	data_allocator_type	_alloc_data;
};

template<typename Key, typename Data, typename Allocator = std::allocator<std::pair<const Key, Data> > >
class map_test
{
public:
	typedef std::pair<const Key, Data>		data_type;
	map_test() : _allocator(), rb_tree(_allocator){
		std::cout << "map created" << std::endl;
	}
	void	insert(const data_type& value){
		rb_tree.create_node(value);
	}
	void	print_node(){
		std::cout << rb_tree->node_p.value;
	}
private:
	Allocator _allocator;
	rb_tree_test<Key, Data, Allocator> rb_tree;
};