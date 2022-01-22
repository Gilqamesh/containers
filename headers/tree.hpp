#ifndef TREE_HPP
# define TREE_HPP

# include "functional.hpp"
# include "algorithm.hpp"
# include "utility.hpp"
# include <string>
# include <iostream>

namespace ft
{

template <class tree>
class tree_iterator;

template <class tree>
class tree_const_iterator
{
public:
	typedef typename tree::node_pointer			node_pointer;
	typedef typename tree::const_pointer		const_pointer;
	typedef typename tree::const_reference		const_reference;

	tree_const_iterator()
		: ptr(NULL), start_node(NULL), end_node(NULL), end_leaf_node(NULL) { }
	tree_const_iterator(node_pointer p, node_pointer start, node_pointer end, node_pointer end_leaf_node)
		: ptr(p), start_node(start), end_node(end), end_leaf_node(end_leaf_node) { }
	tree_const_iterator(const tree_const_iterator& other)
		: ptr(other.ptr), start_node(other.start_node), end_node(other.end_node), end_leaf_node(other.end_leaf_node) { }
	tree_const_iterator(const tree_iterator<tree>& other)
		: ptr(other.ptr), start_node(other.start_node), end_node(other.end_node), end_leaf_node(other.end_leaf_node) { }
	tree_const_iterator& operator=(const tree_const_iterator& other)
	{
		if (this != &other)
		{
			ptr = other.ptr;
			start_node = other.start_node;
			end_node = other.end_node;
			end_leaf_node = other.end_leaf_node;
		}
		return (*this);
	}
	~tree_const_iterator() { }

	const_pointer operator->()
	{
		if (ptr == NULL)
			return (end_node->base.data);
		return (ptr->base.data);
	}
	const_reference operator*()
	{
		if (ptr == NULL)
			return (*end_node->base.data);
		return (*ptr->base.data);
	}
	tree_const_iterator &operator++()
	{
		ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (*this);
	}
	tree_const_iterator operator++(int)
	{
		tree_const_iterator tmp(*this);
		ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (tmp);
	}
	tree_const_iterator &operator--()
	{
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (*this);
	}
	tree_const_iterator operator--(int)
	{
		tree_const_iterator tmp(*this);
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (tmp);
	}
	bool operator==(const tree_const_iterator &other) const
	{
		return (ptr == other.ptr);
		if (ptr == end_node)
		{
			if (other.ptr == other.end_node)
				return (ptr == other.ptr);
			return (false);
		}
		else
		{
			if (other.ptr == other.end_node)
				return (false);
			return (ptr == other.ptr);
		}
	}
	bool operator!=(const tree_const_iterator &other) const
	{
		return (!(*this == other));
	}
private:
	node_pointer ptr;
	node_pointer start_node;
	node_pointer end_node;
	node_pointer end_leaf_node;
};

template <class tree>
class tree_iterator
{
friend class tree_const_iterator<tree>;
public:
	typedef typename tree::node_pointer			node_pointer;
	typedef typename tree::pointer				pointer;
	typedef typename tree::reference			reference;

	tree_iterator()
		: ptr(NULL), start_node(NULL), end_node(NULL), end_leaf_node(NULL) { }
	tree_iterator(node_pointer p, node_pointer start, node_pointer end, node_pointer end_leaf_node)
		: ptr(p), start_node(start), end_node(end), end_leaf_node(end_leaf_node) { }
	tree_iterator(const tree_iterator& other)
		: ptr(other.ptr), start_node(other.start_node), end_node(other.end_node), end_leaf_node(other.end_leaf_node) { }
	tree_iterator& operator=(const tree_iterator& other)
	{
		if (this != &other)
		{
			ptr = other.ptr;
			start_node = other.start_node;
			end_node = other.end_node;
			end_leaf_node = other.end_leaf_node;
		}
		return (*this);
	}
	~tree_iterator() { }

	pointer operator->()
	{
		if (ptr == NULL)
			return (end_node->base.data);
		return (ptr->base.data);
	}
	reference operator*()
	{
		if (ptr == NULL)
			return (*end_node->base.data);
		return (*ptr->base.data);
	}
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
		ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (tmp);
	}
	tree_iterator &operator--()
	{
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (*this);
	}
	tree_iterator operator--(int)
	{
		tree_iterator tmp(*this);
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (tmp);
	}
	bool operator==(const tree_iterator &other) const
	{
		return (ptr == other.ptr);
		if (ptr == end_node)
		{
			if (other.ptr == other.end_node)
				return (ptr == other.ptr);
			return (false);
		}
		else
		{
			if (other.ptr == other.end_node)
				return (false);
			return (ptr == other.ptr);
		}
	}
	bool operator!=(const tree_iterator &other) const
	{
		return (!(*this == other));
	}
private:
	node_pointer ptr;
	node_pointer start_node;
	node_pointer end_node;
	node_pointer end_leaf_node;
};

template <class tree>
class tree_reverse_iterator;

template <class tree>
class tree_const_reverse_iterator
{
public:
	typedef typename tree::node_pointer			node_pointer;
	typedef typename tree::const_pointer		const_pointer;
	typedef typename tree::const_reference		const_reference;

	tree_const_reverse_iterator()
		: ptr(NULL), start_node(NULL), end_node(NULL), end_leaf_node(NULL) { }
	tree_const_reverse_iterator(node_pointer p, node_pointer start, node_pointer end, node_pointer end_leaf_node)
		: ptr(p), start_node(start), end_node(end), end_leaf_node(end_leaf_node) { }
	tree_const_reverse_iterator(const tree_const_reverse_iterator& other)
		: ptr(other.ptr), start_node(other.start_node), end_node(other.end_node), end_leaf_node(other.end_leaf_node) { }
	tree_const_reverse_iterator(const tree_reverse_iterator<tree>& other)
		: ptr(other.ptr), start_node(other.start_node), end_node(other.end_node), end_leaf_node(other.end_leaf_node) { }
	tree_const_reverse_iterator& operator=(const tree_const_reverse_iterator& other)
	{
		if (this != &other)
		{
			ptr = other.ptr;
			start_node = other.start_node;
			end_node = other.end_node;
			end_leaf_node = other.end_leaf_node;
		}
		return (*this);
	}
	~tree_const_reverse_iterator() { }

	const_pointer	operator->()
	{
		if (ptr == NULL)
			return (end_node->base.data);
		return (ptr->base.data);
	}
	const_reference operator*()
	{
		if (ptr == NULL)
			return (*end_node->base.data);
		return (*ptr->base.data);
	}
	tree_const_reverse_iterator &operator++()
	{
		ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (*this);
	}
	tree_const_reverse_iterator operator++(int)
	{
		tree_const_reverse_iterator tmp(*this);
		ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (tmp);
	}
	tree_const_reverse_iterator &operator--()
	{
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (*this);
	}
	tree_const_reverse_iterator operator--(int)
	{
		tree_const_reverse_iterator tmp(*this);
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (tmp);
	}
	bool operator==(const tree_const_reverse_iterator &other) const
	{
		return (ptr == other.ptr);
		if (ptr == end_node)
		{
			if (other.ptr == other.end_node)
				return (ptr == other.ptr);
			return (false);
		}
		else
		{
			if (other.ptr == other.end_node)
				return (false);
			return (ptr == other.ptr);
		}
	}
	bool operator!=(const tree_const_reverse_iterator &other) const
	{
		return (!(*this == other));
	}
private:
	node_pointer ptr;
	node_pointer start_node;
	node_pointer end_node;
	node_pointer end_leaf_node;
};

template <class tree>
class tree_reverse_iterator
{
friend class tree_const_reverse_iterator<tree>;
public:
	typedef typename tree::node_pointer			node_pointer;
	typedef typename tree::pointer				pointer;
	typedef typename tree::reference			reference;

	tree_reverse_iterator()
		: ptr(NULL), start_node(NULL), end_node(NULL), end_leaf_node(NULL) { }
	tree_reverse_iterator(node_pointer p, node_pointer start, node_pointer end, node_pointer end_leaf_node)
		: ptr(p), start_node(start), end_node(end), end_leaf_node(end_leaf_node) { }
	tree_reverse_iterator(const tree_reverse_iterator& other)
		: ptr(other.ptr), start_node(other.start_node), end_node(other.end_node), end_leaf_node(other.end_leaf_node) { }
	tree_reverse_iterator& operator=(const tree_reverse_iterator& other)
	{
		if (this != &other)
		{
			ptr = other.ptr;
			start_node = other.start_node;
			end_node = other.end_node;
			end_leaf_node = other.end_leaf_node;
		}
		return (*this);
	}
	~tree_reverse_iterator() { }

	pointer	operator->()
	{
		if (ptr == NULL)
			return (end_node->base.data);
		return (ptr->base.data);
	}
	reference operator*()
	{
		if (ptr == NULL)
			return (*end_node->base.data);
		return (*ptr->base.data);
	}
	tree_reverse_iterator &operator++()
	{
		ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (*this);
	}
	tree_reverse_iterator operator++(int)
	{
		tree_reverse_iterator tmp(*this);
		ptr = get_predecessor(ptr);
		if (ptr == NULL)
			ptr = end_node;
		return (tmp);
	}
	tree_reverse_iterator &operator--()
	{
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (*this);
	}
	tree_reverse_iterator operator--(int)
	{
		tree_reverse_iterator tmp(*this);
		if (ptr == end_node)
			ptr = end_leaf_node;
		else
			ptr = get_successor(ptr);
		if (ptr == NULL)
			ptr = start_node;
		return (tmp);
	}
	bool operator==(const tree_reverse_iterator &other) const
	{
		return (ptr == other.ptr);
		if (ptr == end_node)
		{
			if (other.ptr == other.end_node)
				return (ptr == other.ptr);
			return (false);
		}
		else
		{
			if (other.ptr == other.end_node)
				return (false);
			return (ptr == other.ptr);
		}
	}
	bool operator!=(const tree_reverse_iterator &other) const
	{
		return (!(*this == other));
	}
private:
	node_pointer ptr;
	node_pointer start_node;
	node_pointer end_node;
	node_pointer end_leaf_node;
};

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

	node()
		: base(), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
	node(const value_type& item)
		: base(item), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
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
	typedef typename NodeContainer::key_compare							key_compare;
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

	typedef tree_iterator<red_black_tree> 								iterator;
	typedef tree_const_iterator<red_black_tree>							const_iterator;
	typedef tree_reverse_iterator<red_black_tree>						reverse_iterator;
	typedef tree_const_reverse_iterator<red_black_tree>					const_reverse_iterator;

	red_black_tree(void)
		: root(NULL), begin_node(new node_type()), end_node(new node_type()) { }
	red_black_tree(const red_black_tree& other)
		: root(NULL), begin_node(new node_type()), end_node(new node_type())
	{
		for (const_iterator c_it = other.begin(); c_it != other.end(); ++c_it)
			insert(*c_it);
	}
	~red_black_tree(void)
	{
		delete_from_node(root);
		root = NULL;
		delete begin_node;
		begin_node = NULL;
		delete end_node;
		end_node = NULL;
	}
	red_black_tree& operator=(const red_black_tree& other)
	{
		if (this != &other)
		{
			delete_from_node(root);
			root = NULL;
			for (const_iterator c_it = other.begin(); c_it != other.end(); ++c_it)
				insert(*c_it);
		}
		return (*this);
	}

	iterator		 begin(void)  { return (iterator		(find_left_most_leaf(root), begin_node, end_node, find_right_most_leaf(root))); }
	iterator		 end(void)	  { return (iterator		(end_node, begin_node, end_node, find_right_most_leaf(root))); 					}
	reverse_iterator rbegin(void) { return (reverse_iterator(find_right_most_leaf(root), end_node, begin_node, find_left_most_leaf(root)));	}
	reverse_iterator rend(void)	  { return (reverse_iterator(begin_node, end_node, begin_node, find_left_most_leaf(root)));					}

	const_iterator		   begin(void)	const { return (iterator		(find_left_most_leaf(root), begin_node, end_node, find_right_most_leaf(root))); }
	const_iterator		   end(void)	const { return (iterator		(end_node, begin_node, end_node, find_right_most_leaf(root))); 					}
	const_reverse_iterator rbegin(void) const { return (reverse_iterator(find_right_most_leaf(root), end_node, begin_node, find_left_most_leaf(root)));	}
	const_reverse_iterator rend(void)	const { return (reverse_iterator(begin_node, end_node, begin_node, find_left_most_leaf(root)));					}

	node_pointer		search(const key_type& key)		  { return (search_from_node(key, root, NodeContainer::compare)); }
	node_const_pointer	search(const key_type& key) const { return (search_from_node(key, root, NodeContainer::compare)); }
	node_pointer 		insert(const value_type& item)
	{

		node_pointer z = new node_type(item);
		node_pointer y = NULL;
		node_pointer x = root;
		while (x != NULL)
		{
			y = x;
			if (NodeContainer::compare(z->base.getKey(), x->base.getKey()))
				x = x->left_child;
			else
				x = x->right_child;
		}
		z->parent = y;
		if (y == NULL)
			root = z;
		else if (NodeContainer::compare(z->base.getKey(), y->base.getKey()))
			y->left_child = z;
		else
			y->right_child = z;
		insert_fixup(z, &root);
		return (z);
	}
	void 			remove(const key_type& key)
	{
		node_pointer Node = search(key, root);
		if (Node == NULL)
			return ;
		
		Node = make_node_leaf(Node);

		if (Node->color == BLACK)
			delete_fixup(Node, &root);
		
		prune_leaf(Node);
	}

	// DEBUG
	void print(void) const { print("", root, false); }
private:
	node_pointer	root;
	node_pointer	begin_node;
	node_pointer	end_node;

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
void insert_fixup(node_pointer z, node_pointer *root)
{
	if (z == NULL)
		return ;
	while (z != *root && z->parent->color == RED)
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
	(*root)->color = BLACK;
}

template <class node_pointer>
void left_rotate(node_pointer x, node_pointer *root)
{
	if (x == NULL)
		return ;
	node_pointer y = x->right_child;
	x->right_child = y->left_child;
	if (y->left_child)
		y->left_child->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		*root = y;
	else if (x == x->parent->left_child)
		x->parent->left_child = y;
	else
		x->parent->right_child = y;
	y->left_child = x;
	x->parent = y;
}

template <class node_pointer>
void right_rotate(node_pointer x, node_pointer *root)
{
	if (x == NULL)
		return ;
	node_pointer y = x->left_child;
	x->left_child = y->right_child;
	if (y->right_child)
		y->right_child->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		*root = y;
	else if (x == x->parent->left_child)
		x->parent->left_child = y;
	else
		x->parent->right_child = y;
	y->right_child = x;
	x->parent = y;
}

template <class node_pointer>
void delete_from_node(node_pointer x)
{
	if (x == NULL)
		return ;
	if (x->left_child)
		delete_from_node(x->left_child);
	if (x->right_child)
		delete_from_node(x->right_child);
	delete x;
}

template <class node_pointer>
void delete_fixup(node_pointer x, node_pointer *root)
{
	if (x == NULL)
		return ;
	while (x != *root && x->color == BLACK)
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
			x = *root;
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
void	rotate_to_parent(node_pointer Node, node_pointer *root)
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

template <class node_pointer>
node_pointer make_node_leaf(node_pointer Node)
{
	if (Node == NULL)
		return (NULL);
	if (Node->left_child == NULL && Node->right_child == NULL)
		return (Node);
	if (has_one_child(Node))
	{
		Node->swap(*Node, *has_one_child(Node));
		Node = has_one_child(Node);
		return (make_node_leaf(Node));
	}
	else
	{
		Node->swap(*Node, *get_predecessor(Node));
		Node = get_predecessor(Node);
		return (make_node_leaf(Node));
	}
}

template <class node_pointer>
void	prune_leaf(node_pointer leaf)
{
	if (leaf == NULL)
		return ;
	if (leaf->parent)
	{
		if (leaf == leaf->parent->left_child)
			leaf->parent->left_child = NULL;
		else
			leaf->parent->right_child = NULL;
	}
	std::cout << "Removing " << leaf->getKey() << std::endl;
	delete leaf;
}

} // ft

#endif
