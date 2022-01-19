#ifndef TREE_HPP
# define TREE_HPP

# include "functional.hpp"
# include "algorithm.hpp"
# include "utility.hpp"
# include <string>
# include <iostream>

namespace ft
{

template <class base_node>
class red_black_tree
{
public:
	typedef typename base_node::key_type			key_type;
	typedef typename base_node::value_type			value_type;
	typedef typename base_node::key_compare			key_compare;

private:
	enum color_type
	{
		BLACK,
		RED
	};

	/*
	* The inherit class needs to have swap() and getKey() methods
	*/
	class node : public base_node
	{
	public:
		node()
			: base_node(), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
		node(const value_type& item)
			: base_node(item), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
		node(const node& other)
			: base_node(other), color(other.color), left_child(other.left_child), right_child(other.right_child), parent(other.parent) { }
		node& operator=(const node& other)
		{
			if (this != &other)
			{
				base_node::operator=(other);
				color = other.color;
				left_child = other.left_child;
				right_child = other.right_child;
				parent = other.parent;
			}
			return (*this);
		}
		~node() { }

		color_type	color;
		node		*left_child;
		node		*right_child;
		node		*parent;
	};

public:
	typedef node*	node_pointer;
	node			*root;

	red_black_tree()
		: root(NULL) { }
	~red_black_tree() { delete_from_node(root); }

	node 	*search(const key_type& key) { return (search(key, root)); }
	void 	insert(const value_type& item)
	{
		node *z = new node(item);
		node *y = NULL;
		node *x = root;
		while (x != NULL)
		{
			y = x;
			if (key_compare()(z->getKey(), x->getKey()))
				x = x->left_child;
			else
				x = x->right_child;
		}
		z->parent = y;
		if (y == NULL)
			root = z;
		else if (z->getKey() < y->getKey())
			y->left_child = z;
		else
			y->right_child = z;
		insert_fixup(z);
	}
	void 	remove(const key_type& key)
	{
		node*	Node = search(key);
		if (Node == NULL)
			return ;
		
		Node = make_node_leaf(Node);

		if (Node->color == BLACK)
			delete_fixup(Node);
		
		prune_leaf(Node);
	}

	// DEBUG
	void	print(void) const { print("", root, false); }

	node *search(const key_type& key, node *x)
	{
		if (x == NULL)
			return (NULL);
		if (key == x->getKey())
			return (x);
		if (key_compare()(key, x->getKey()))
			return (search(key, x->left_child));
		else
			return (search(key, x->right_child));
	}
	void insert_fixup(node* z)
	{
		while (z != root && z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->left_child)
			{
				node*	y = z->parent->parent->right_child; // z's uncle
				if (y == NULL || y->color == BLACK)
				{
					if (z == z->parent->right_child) // triangle
					{
						z = z->parent;
						left_rotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					right_rotate(z->parent->parent);
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
				node*	y = z->parent->parent->left_child;
				if (y == NULL || y->color == BLACK)
				{
					if (z == z->parent->left_child)
					{
						z = z->parent;
						right_rotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					left_rotate(z->parent->parent);
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
	void left_rotate(node* x)
	{
		node*	y = x->right_child;
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
	void right_rotate(node *x)
	{
		node*	y = x->left_child;
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
	void delete_from_node(node* x)
	{
		if (x == NULL)
			return ;
		if (x->left_child)
			delete_from_node(x->left_child);
		if (x->right_child)
			delete_from_node(x->right_child);
		delete x;
	}
	void delete_fixup(node* x)
	{
		if (x == NULL)
			return ;
		while (x != root && x->color == BLACK)
		{
			if (sibling(x) && sibling(x)->color == RED)
			{
				x->parent->color = RED;
				sibling(x)->color = BLACK;
				rotate_to_parent(sibling(x));
			}
			else if (nephew(x) && nephew(x)->color == RED)
			{
				sibling(x)->color = x->parent->color;
				x->parent->color = BLACK;
				nephew(x)->color = BLACK;
				rotate_to_parent(sibling(x));
				x = root;
				break ;
			}
			else if (niece(x) && niece(x)->color == RED)
			{
				niece(x)->color = BLACK;
				sibling(x)->color = RED;
				rotate_to_parent(sibling(x));
			}
			else
			{
				sibling(x)->color = RED;
				x = x->parent;
			}
		}

		x->color = BLACK;
	}
	node *get_successor(node* Node)
	{
		if (Node == NULL)
			return (NULL);
		if (Node->right_child)
			return (find_left_most_leaf(Node->right_child));
		
		node*	p = Node->parent;
		while (p && Node == p->right_child)
		{
			Node = p;
			p = p->parent;
		}
		return (p);
	}
	node *get_predecessor(node *Node)
	{
		if (Node == NULL)
			return (NULL);
		if (Node->left_child)
			return (find_right_most_leaf(Node->left_child));
		
		node*	p = Node->parent;
		while (p && Node == p->left_child)
		{
			Node = p;
			p = p->parent;
		}
		return (p);
	}
	node *find_left_most_leaf(node* Node)
	{
		while (Node->left_child)
			Node = Node->left_child;
		return (Node);
	}
	node *find_right_most_leaf(node* Node)
	{
		while (Node->right_child)
			Node = Node->right_child;
		return (Node);
	}
	node *sibling(node* Node)
	{
		if (Node->parent == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (Node->parent->right_child);
		return (Node->parent->left_child);
	}
	node *niece(node* Node)
	{
		if (sibling(Node) == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (sibling(Node)->left_child);
		return (sibling(Node)->right_child);
	}
	node *nephew(node* Node)
	{
		if (sibling(Node) == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (sibling(Node)->right_child);
		return (sibling(Node)->left_child);
	}
	void	rotate_to_parent(node* Node)
	{
		if (Node == Node->parent->left_child)
			right_rotate(Node->parent);
		else
			left_rotate(Node->parent);
	}
	node	*has_one_child(node* Node)
	{
		if (Node->left_child && Node->right_child == NULL)
			return (Node->left_child);
		if (Node->left_child == NULL && Node->right_child)
			return (Node->right_child);
		return (NULL);
	}
	node	*make_node_leaf(node* Node)
	{
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
	void	prune_leaf(node* leaf)
	{
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

	// DEBUG
	void	print(const std::string& prefix, node* x, bool isLeft) const
	{
		if (x)
		{
			std::cout << prefix;
			std::cout << (isLeft ? "├──" : "└──");
			std::cout << x->getKey() << (x->color == BLACK ? " black" : " red" ) << std::endl;
			print(prefix + (isLeft ? "│   " : "    "), x->left_child, true);
			print(prefix + (isLeft ? "│   " : "    "), x->right_child, false);
		}
	}
};

} // ft

#endif
