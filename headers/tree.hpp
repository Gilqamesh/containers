#ifndef TREE_HPP
# define TREE_HPP

# include "functional.hpp"
# include "algorithm.hpp"
# include "utility.hpp"
# include "iterator.hpp"
# include <string>

# include <iostream>
# define PRINT_HERE() (std::cout << __FILE__ << " " << __LINE__ << std::endl)

namespace ft
{

// T pair
template <typename NodePtr, typename T>
class tree_iterator
{
public:
	typedef iterator<bidirectional_iterator_tag, T>							iterator_type;
	typedef typename iterator_traits<iterator_type>::difference_type		difference_type;
	typedef typename iterator_traits<iterator_type>::value_type				value_type;
	typedef typename iterator_traits<iterator_type>::pointer				pointer;
	typedef typename iterator_traits<iterator_type>::reference				reference;
	typedef typename iterator_traits<iterator_type>::iterator_category		iterator_category;

	tree_iterator()
		: ptr(NULL), start_leaf_node(NULL), end_node(NULL), end_leaf_node(NULL) { }
	tree_iterator(NodePtr p, NodePtr start_leaf, NodePtr end, NodePtr end_leaf)
		: ptr(p == NULL ? end : p), start_leaf_node(start_leaf), end_node(end), end_leaf_node(end_leaf) { }
	tree_iterator(const tree_iterator& other)
		: ptr(other.base()), start_leaf_node(other.start_leaf_node), end_node(other.end_node), end_leaf_node(other.end_leaf_node) { }
	tree_iterator& operator=(const tree_iterator& other)
	{
		if (this != &other)
		{
			ptr = other.ptr;
			start_leaf_node = other.start_leaf_node;
			end_node = other.end_node;
			end_leaf_node = other.end_leaf_node;
		}
		return (*this);
	}
	~tree_iterator() { }
	operator tree_iterator<NodePtr, const T>() const { return (tree_iterator<NodePtr, const T>(ptr, start_leaf_node, end_node, end_leaf_node)); }
	tree_iterator &operator++()
	{
		ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (*this);
	}
	tree_iterator operator++(int)
	{
		tree_iterator tmp(*this);
		++*this;
		return (tmp);
	}
	tree_iterator &operator--()
	{
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_predecessor(ptr);
		return (*this);
	}
	tree_iterator operator--(int)
	{
		tree_iterator tmp(*this);
		--*this;
		return (tmp);
	}
	reference operator*() const
	{
		return (ptr->base.data);
	}
	pointer operator->() const
	{
		return (&ptr->base.data);
	}
	NodePtr base() const
	{
		return (ptr);
	}

private:
	NodePtr 	ptr;
	NodePtr		start_leaf_node;
	NodePtr 	end_node;
	NodePtr 	end_leaf_node;
};

template <typename NodePtr, class T1, class T2>
bool operator==(const tree_iterator<NodePtr, T1>& lhs, const tree_iterator<NodePtr, T2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename NodePtr, class T1, class T2>
bool operator!=(const tree_iterator<NodePtr, T1>& lhs, const tree_iterator<NodePtr, T2>& rhs)
{
	return (lhs.base() != rhs.base());
}

enum color_type
{
	BLACK,
	RED
};

/*
* The inherit class needs to have swap() and getKey() methods
*/
template <class node_type>
class node
{
public:
	typedef typename node_type::key_type		key_type;
	typedef typename node_type::value_type		value_type;
	typedef typename node_type::pointer			pointer;
	typedef typename node_type::reference		reference;
	typedef ptrdiff_t							difference_type;
	typedef bidirectional_iterator_tag			iterator_category;

	node()
		: base(), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
	node(const value_type& item)
		: base(item), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
	node(node_type b, color_type c, node *left, node *right, node *p)
		: base(b), color(c), left_child(left), right_child(right), parent(p) { }
	node(const node& other)
		: base(other.base), color(other.color), left_child(other.left_child), right_child(other.right_child), parent(other.parent) { }
	node& operator=(const node& other)
	{
		if (this != &other)
		{
			base = other.base;
			color = other.color;
			left_child = other.left_child;
			right_child = other.right_child;
			parent = other.parent;
		}
		return (*this);
	}
	operator node<const node_type>() const { return (node<const node_type>(base, color, left_child, right_child, parent)); }
	~node() { }

	node_type	base;
	color_type	color;
	node		*left_child;
	node		*right_child;
	node		*parent;
};

template <class NodeContainer>
class red_black_tree
{
public:
	typedef typename NodeContainer::key_type							key_type;
	typedef typename NodeContainer::mapped_type							mapped_type;
	typedef typename NodeContainer::value_type							value_type;
	typedef typename NodeContainer::size_type							size_type;
	typedef typename NodeContainer::key_compare							key_compare;
	typedef typename NodeContainer::allocator_type						allocator_type;
	typedef typename NodeContainer::reference							reference;
	typedef typename NodeContainer::const_reference						const_reference;
	typedef typename NodeContainer::pointer								pointer;
	typedef typename NodeContainer::const_pointer						const_pointer;

	typedef typename NodeContainer::base_node_type						base_node_type;
	typedef typename NodeContainer::base_node_pointer					base_node_pointer;
	typedef typename NodeContainer::base_node_const_pointer				base_node_const_pointer;
	typedef typename NodeContainer::base_node_reference					base_node_reference;
	typedef typename NodeContainer::base_node_const_reference			base_node_const_reference;

	typedef node<base_node_type>										node_type;
	typedef node<base_node_type>*										node_pointer;
	typedef const node<base_node_type>*									node_const_pointer;
	typedef node<base_node_type>&										node_reference;
	typedef const node<base_node_type>&									node_const_reference;
	typedef typename allocator_type::template rebind<node_type>::other	node_allocator_type;

	typedef tree_iterator<node_pointer, value_type> 					iterator;
	typedef tree_iterator<node_pointer, const value_type>				const_iterator;
	typedef ft::reverse_iterator<iterator>								reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

	red_black_tree()
		: root(NULL), end_node(NULL)
	{
		end_node = allocator.allocate(sizeof(*end_node));
		allocator.construct(end_node, node_type());
	}
	red_black_tree(const red_black_tree& other)
		: root(NULL), end_node(NULL)
	{
		end_node = allocator.allocate(sizeof(*end_node));
		allocator.construct(end_node, node_type());
		for (const_iterator c_it = other.begin(); c_it != other.end(); ++c_it)
			insert(*c_it);
	}
	~red_black_tree()
	{
		delete_from_node(root, allocator);
		allocator.destroy(end_node);
		allocator.deallocate(end_node, sizeof(*end_node));
		root = NULL;
		end_node = NULL;
	}
	red_black_tree& operator=(const red_black_tree& other)
	{
		if (this != &other)
		{
			delete_from_node(root, allocator);
			for (const_iterator c_it = other.begin(); c_it != other.end(); ++c_it)
				insert(*c_it);
		}
		return (*this);
	}

	iterator		 begin(void)  { return (iterator		(find_left_most_leaf(root), find_left_most_leaf(root), end_node, find_right_most_leaf(root)));		}
	iterator		 end(void)	  { return (iterator		(end_node, find_left_most_leaf(root), end_node, find_right_most_leaf(root))); 						}
	reverse_iterator rbegin(void) { return (reverse_iterator(iterator(end_node, find_left_most_leaf(root), end_node, find_right_most_leaf(root))));	}
	reverse_iterator rend(void)	  { return (reverse_iterator(iterator(find_left_most_leaf(root), find_left_most_leaf(root), end_node, find_right_most_leaf(root))));					}
	const_iterator		   begin(void) 	const { return (iterator		(find_left_most_leaf(root), find_left_most_leaf(root), end_node, find_right_most_leaf(root)));		}
	const_iterator		   end(void) 	const { return (iterator		(end_node, find_left_most_leaf(root), end_node, find_right_most_leaf(root))); 						}
	const_reverse_iterator rbegin(void) const { return (reverse_iterator(iterator(end_node, find_left_most_leaf(root), end_node, find_right_most_leaf(root))));	}
	const_reverse_iterator rend(void) 	const { return (reverse_iterator(iterator(find_left_most_leaf(root), find_left_most_leaf(root), end_node, find_right_most_leaf(root))));					}

	size_t max_size(void) const { return (allocator.max_size()); }
	iterator get_iterator_at(node_pointer p) const { return (iterator(p, find_left_most_leaf(root), end_node, find_right_most_leaf(root))); }

	node_pointer		search(const key_type& key)	const { return (search_from_node(key, root, compare)); }
	node_pointer 		insert(const value_type& item)
	{
		node_pointer z = allocator.allocate(sizeof(*z));
		allocator.construct(z, node_type(item));
		node_pointer y = NULL;
		node_pointer x = root;
		while (x != NULL)
		{
			y = x;
			if (compare(z->base.getKey(), x->base.getKey()))
				x = x->left_child;
			else
				x = x->right_child;
		}
		z->parent = y;
		if (y == NULL)
			root = z;
		else if (compare(z->base.getKey(), y->base.getKey()))
			y->left_child = z;
		else
			y->right_child = z;
		insert_fixup(z, root);
		return (z);
	}
	node_pointer 		insert(iterator hint, const value_type& item)
	{
		node_pointer z = allocator.allocate(sizeof(*z));
		allocator.construct(z, node_type(item));
		node_pointer y = NULL;
		node_pointer x = hint.base();
		while (x != NULL)
		{
			y = x;
			if (compare(z->base.getKey(), x->base.getKey()))
				x = x->left_child;
			else
				x = x->right_child;
		}
		z->parent = y;
		if (y == NULL)
			root = z;
		else if (compare(z->base.getKey(), y->base.getKey()))
			y->left_child = z;
		else
			y->right_child = z;
		insert_fixup(z, root);
		return (z);
	}
	void 			remove(const key_type& key)
	{
		node_pointer Node = search(key);
		if (Node == NULL)
			return ;
		
		if (Node->left_child == NULL && Node->right_child == NULL)
		{
			if (Node->parent)
			{
				if (Node->parent->left_child == Node)
					Node->parent->left_child = NULL;
				else
					Node->parent->right_child = NULL;
			}
			if (Node->color == BLACK)
				delete_fixup(Node->parent, root);
			if (Node->parent == NULL)
				root = NULL;
		}
		else if (has_one_child(Node)) // Node is black cause red cant have exactly 1 child
		{
			// shift the child up and change its color to black
			node_pointer child = has_one_child(Node);
			node_pointer parent = Node->parent;
			if (Node->parent) // if Node is not root
			{
				if (Node == parent->left_child)
					parent->left_child = child;
				else
					parent->right_child = child;
			}
			else
				root = child;
			child->parent = parent;
			child->color = BLACK;
		}
		else
		{
			// swap with successor
			node_pointer successor = get_successor(Node);
			swap_nodes(Node, successor, root);
			if (Node->color == BLACK)
			{
				node_pointer child = has_one_child(Node);
				if (child) // shift the child to this node
					child->parent = Node->parent;
				if (Node->parent)
				{
					if (Node->parent->left_child == Node)
						Node->parent->left_child = child;
					else
						Node->parent->right_child = child;
				}
				if (child)
					delete_fixup(child, root);
				else
					delete_fixup(Node->parent, root);
			}
			else 
			{
				if (Node->parent)
				{
					if (Node->parent->left_child == Node)
						Node->parent->left_child = NULL;
					else
						Node->parent->right_child = NULL;
				}
			}
		}
		
		prune_leaf(Node, allocator);
	}
	void clear(void) { delete_from_node(root, allocator); }

	// DEBUG
	void print(void) const { print("", root, false); }
private:
	node_pointer		root;
	node_pointer		end_node;
	key_compare			compare;
	node_allocator_type	allocator;

	void	print(const std::string& prefix, node_pointer x, bool isLeft) const
	{
		if (x)
		{
			std::cout << prefix;
			std::cout << (isLeft ? "├──" : "└──");
			std::cout << x->base.getKey() << (x->color == BLACK ? " black" : " red" ) << std::endl;
			print(prefix + (isLeft ? "│   " : "    "), x->left_child, true);
			print(prefix + (isLeft ? "│   " : "    "), x->right_child, false);
		}
	}
};

// swaps the references but not the data
template <class node_pointer>
void swap_nodes(node_pointer node1, node_pointer node2, node_pointer &root)
{
	ft::swap(node1->color, node2->color);
	if (node1->parent == node2 || node2->parent == node1) // one is the other's parent
	{
		if (node1->parent == node2) // so that 1 is 2's parent
			ft::swap(node1, node2);
		node_pointer three = node2->left_child;
		node_pointer four = node2->right_child;
		node_pointer five = node1->parent;
		bool isNode2LeftChild = (node1->left_child == node2);
		node_pointer six = (isNode2LeftChild ? node1->right_child : node1->left_child);
		if (five)
		{
			if (five->left_child == node1)
				five->left_child = node2;
			else
				five->right_child = node2;
		}
		else
			root = node2;
		node2->parent = five;
		if (isNode2LeftChild)
		{
			node2->left_child = node1;
			node2->right_child = six;
		}
		else
		{
			node2->left_child = six;
			node2->right_child = node1;
		}
		node1->parent = node2;
		node1->left_child = three;
		node1->right_child = four;
		if (three)
			three->parent = node1;
		if (four)
			four->parent = node1;
		if (six)
			six->parent = node2;
	}
	else
	{
		node_pointer three = node2->left_child;
		node_pointer four = node2->right_child;
		node_pointer eight = node2->parent;
		node_pointer seven = node1->left_child;
		node_pointer six = node1->right_child;
		node_pointer five = node1->parent;
		node1->left_child = three;
		node1->right_child = four;
		node1->parent = eight;
		node2->left_child = seven;
		node2->right_child = six;
		node2->parent = five;
		if (three)
			three->parent = node1;
		if (four)
			four->parent = node1;
		if (eight)
		{
			if (eight->left_child == node2)
				eight->left_child = node1;
			else
				eight->right_child = node1;
		}
		if (seven)
			seven->parent = node2;
		if (six)
			six->parent = node2;
		if (five)
		{
			if (five->left_child == node1)
				five->left_child = node2;
			else
				five->right_child = node2;
		}
		else
			root = node2;
	}
}

template <class node_pointer>
node_pointer getRoot(node_pointer a)
{
	if (a == NULL)
		return (NULL);
	while (a->parent)
		a = a->parent;
	return (a);
}

template <class node_pointer, typename key_type, class key_compare>
node_pointer search_from_node(const key_type& key, node_pointer x, key_compare compare)
{
	if (x == NULL)
		return (NULL);
	if (key == x->base.getKey())
		return (x);
	if (compare(key, x->base.getKey()))
		return (search_from_node(key, x->left_child, compare));
	else
		return (search_from_node(key, x->right_child, compare));
}

template <class node_pointer>
void insert_fixup(node_pointer z, node_pointer &root)
{
	if (z == NULL)
		return ;
	while (z != root && z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left_child)
		{
			node_pointer y = z->parent->parent->right_child; // z's uncle
			if (y == NULL || y->color == BLACK)
			{
				if (z == z->parent->right_child) // triangle
				{
					z = z->parent;
					left_rotate(z, root);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent, root);
			}
			else
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
		}
		else
		{
			node_pointer y = z->parent->parent->left_child;
			if (y == NULL || y->color == BLACK)
			{
				if (z == z->parent->left_child)
				{
					z = z->parent;
					right_rotate(z, root);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent, root);
			}
			else
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
		}
	}
	root->color = BLACK;
}

template <class node_pointer>
void left_rotate(node_pointer x, node_pointer &root)
{
	if (x == NULL)
		return ;
	node_pointer y = x->right_child;
	x->right_child = y->left_child;
	if (y->left_child)
		y->left_child->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else if (x == x->parent->left_child)
		x->parent->left_child = y;
	else
		x->parent->right_child = y;
	y->left_child = x;
	x->parent = y;
}

template <class node_pointer>
void right_rotate(node_pointer x, node_pointer &root)
{
	if (x == NULL)
		return ;
	node_pointer y = x->left_child;
	x->left_child = y->right_child;
	if (y->right_child)
		y->right_child->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		root = y;
	else if (x == x->parent->left_child)
		x->parent->left_child = y;
	else
		x->parent->right_child = y;
	y->right_child = x;
	x->parent = y;
}

template <class node_pointer, class Allocator>
void delete_from_node(node_pointer &x, Allocator allocator)
{
	if (x == NULL)
		return ;
	if (x->left_child)
		delete_from_node(x->left_child, allocator);
	if (x->right_child)
		delete_from_node(x->right_child, allocator);
	allocator.destroy(x);
	allocator.deallocate(x, sizeof(*x));
	x = NULL;
}

template <class node_pointer>
void delete_fixup(node_pointer x, node_pointer &root)
{
	if (x == NULL)
		return ;
	while (x != root && x->color == BLACK)
	{
		if (sibling(x) && sibling(x)->color == RED)
		{
			x->parent->color = RED;
			sibling(x)->color = BLACK;
			rotate_to_parent(sibling(x), root);
		}
		else if (nephew(x) && nephew(x)->color == RED)
		{
			sibling(x)->color = x->parent->color;
			x->parent->color = BLACK;
			nephew(x)->color = BLACK;
			rotate_to_parent(sibling(x), root);
			x = root;
			break ;
		}
		else if (niece(x) && niece(x)->color == RED)
		{
			niece(x)->color = BLACK;
			sibling(x)->color = RED;
			rotate_to_parent(sibling(x), root);
		}
		else
		{
			sibling(x)->color = RED;
			x = x->parent;
		}
	}

	x->color = BLACK;
}

template <class node_pointer>
node_pointer get_successor(node_pointer Node)
{
	if (Node == NULL)
		return (NULL);
	if (Node->right_child)
		return (find_left_most_leaf(Node->right_child));
	
	node_pointer p = Node->parent;
	while (p && Node == p->right_child)
	{
		Node = p;
		p = p->parent;
	}
	return (p);
}

template <class node_pointer>
node_pointer get_predecessor(node_pointer Node)
{
	if (Node == NULL)
		return (NULL);
	if (Node->left_child)
		return (find_right_most_leaf(Node->left_child));
	
	node_pointer p = Node->parent;
	while (p && Node == p->left_child)
	{
		Node = p;
		p = p->parent;
	}
	return (p);
}

template <class node_pointer>
node_pointer find_left_most_leaf(node_pointer Node)
{
	if (Node == NULL)
		return (NULL);
	while (Node->left_child)
		Node = Node->left_child;
	return (Node);
}

template <class node_pointer>
node_pointer find_right_most_leaf(node_pointer Node)
{
	if (Node == NULL)
		return (NULL);
	while (Node->right_child)
		Node = Node->right_child;
	return (Node);
}

template <class node_pointer>
node_pointer sibling(node_pointer Node)
{
	if (Node == NULL || Node->parent == NULL)
		return (NULL);
	if (Node == Node->parent->left_child)
		return (Node->parent->right_child);
	return (Node->parent->left_child);
}

template <class node_pointer>
node_pointer niece(node_pointer Node)
{
	if (sibling(Node) == NULL)
		return (NULL);
	if (Node == Node->parent->left_child)
		return (sibling(Node)->left_child);
	return (sibling(Node)->right_child);
}

template <class node_pointer>
node_pointer nephew(node_pointer Node)
{
	if (sibling(Node) == NULL)
		return (NULL);
	if (Node == Node->parent->left_child)
		return (sibling(Node)->right_child);
	return (sibling(Node)->left_child);
}

template <class node_pointer>
void	rotate_to_parent(node_pointer Node, node_pointer &root)
{
	if (Node == NULL)
		return ;
	if (Node == Node->parent->left_child)
		right_rotate(Node->parent, root);
	else
		left_rotate(Node->parent, root);
}

template <class node_pointer>
node_pointer has_one_child(node_pointer Node)
{
	if (Node == NULL)
		return (NULL);
	if (Node->left_child && Node->right_child == NULL)
		return (Node->left_child);
	if (Node->left_child == NULL && Node->right_child)
		return (Node->right_child);
	return (NULL);
}

template <class node_pointer, class Allocator>
void	prune_leaf(node_pointer leaf, Allocator allocator)
{
	if (leaf == NULL)
		return ;
	#ifndef NDEBUG
		std::cout << "Removing " << leaf->base.getKey() << std::endl;
	#endif
	allocator.destroy(leaf);
	allocator.deallocate(leaf, sizeof(*leaf));
}

} // ft

#endif
