#ifndef TREE_HPP
# define TREE_HPP

// smaller nodes to the left, larger nodes to the right

// 1. A node is either red or black.
// 2. The root and leaves (NIL) are black.
// 3. If a node is red, then its children are black.
// 4. All paths from a node to its NIL descendants contain the same number of black nodes.

// Rotation:
// insert and remove may violate the above rules, so we use rotation to:
// 1. alter the structure of the tree by rearranging subtrees.
// 2. goal is to decrease the height of the tree.
//		- red-black trees: maximum height of O(log n)
//		- larger subtrees up, smaller subtrees down
// 3. does not affect the order of elements.
// Left rotate:
// 1. Root's right child becomes root and old root as it's left child
// 2. New root's old left child becomes old root's right child
// Right rotate:
// 1. Root's left child becomes root and old root as it's right child
// 2. New root's old right child becomes old root's left child
// note: The property of a binary search tree is still preserved after rotaton

// Insertion strategy:
// 1. Insert Z and color it red
// 2. Recolor and rotate nodes to fix violation
// Violation happens when we have either of the 4 cases:
// 0. Z is root -> color Z black
// 1. Z.uncle is red -> recolor Z's parent, grandparent and uncle
// 2. Z.uncle is black (triangle) -> rotate Z.parent in the opposite direction of Z
// 3. Z.uncle is black (line) -> rotate Z.grandparent in the opposite direction of Z and color Z's original parent and grandparent

# include "functional.hpp"
# include "algorithm.hpp"

// DEBUG
# include <string>
# include <iostream>

namespace ft
{

template <typename T, class Compare = ft::less<T> >
class red_black_tree
{
private:
	enum color_type
	{
		BLACK,
		RED
	};
public:
	template <typename U>
	class node
	{
	friend class red_black_tree;
	public:
		node()
			: value(), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
		node(const U i)
			: value(i), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
		node(const U& i, char color)
			: value(i), color(color), left_child(NULL), right_child(NULL), parent(NULL) { }
		node(const node& other)
			: value(other.value), color(other.color), left_child(other.left_child), right_child(other.right_child), parent(other.parent) { }
		node &operator=(const node& other)
		{
			if (this != &other)
			{
				value = other.value;
				color = other.color;
				left_child = other.left_child;
				right_child = other.right_child;
				parent = other.parent;
			}
			return (*this);
		}
		~node() { }

	private:
		U 			value;
		color_type	color;
		node*		left_child;
		node*		right_child;
		node*		parent;
	};

	red_black_tree()
		: root(NULL) { }
	~red_black_tree() { delete_from_node(root); }

	node<T> *search(const T& item) { return (search(item, root)); }
	void 	insert(const T& item)
	{
		node<T>* z = new node<T>(item);
		node<T>* y = NULL;
		node<T>* x = root;
		while (x != NULL)
		{
			y = x;
			if (Compare()(z->value, x->value))
				x = x->left_child;
			else
				x = x->right_child;
		}
		z->parent = y;
		if (y == NULL)
			root = z;
		else if (z->value < y->value)
			y->left_child = z;
		else
			y->right_child = z;
		insert_fixup(z);
	}
	void	remove(const T& item)
	{
		node<T>*	Node = search(item);
		if (Node == NULL)
			return ;
		
		Node = make_node_leaf(Node);

		if (Node->color == BLACK)
			delete_fixup(Node);
		
		prune_leaf(Node);
	}

	// DEBUG
	void	print(void) const { print("", root, false); }

private:
	node<T>*	root;

	node<T> *search(const T& item, node<T> *x)
	{
		if (x == NULL)
			return (NULL);
		if (item == x->value)
			return (x);
		if (Compare()(item, x->value))
			return (search(item, x->left_child));
		else
			return (search(item, x->right_child));
	}
	void insert_fixup(node<T>* z)
	{
		while (z != root && z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->left_child)
			{
				node<T>*	y = z->parent->parent->right_child; // z's uncle
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
				node<T>*	y = z->parent->parent->left_child;
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
	void left_rotate(node<T>* x)
	{
		node<T>*	y = x->right_child;
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
	void right_rotate(node<T> *x)
	{
		node<T>*	y = x->left_child;
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
	void delete_from_node(node<T>* x)
	{
		if (x == NULL)
			return ;
		if (x->left_child)
			delete_from_node(x->left_child);
		if (x->right_child)
			delete_from_node(x->right_child);
		delete x;
	}
	void delete_fixup(node<T>* x)
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
	node<T> *get_successor(node<T>* Node)
	{
		if (Node->right_child)
			return (find_left_most_leaf(Node->right_child));
		
		node<T>*	p = Node->parent;
		while (p && Node == p->right_child)
		{
			Node = p;
			p = p->parent;
		}
		return (p);
	}
	node<T> *get_predecessor(node<T> *Node)
	{
		if (Node->left_child)
			return (find_right_most_leaf(Node->left_child));
		
		node<T>*	p = Node->parent;
		while (p && Node == p->left_child)
		{
			Node = p;
			p = p->parent;
		}
		return (p);
	}
	node<T> *find_left_most_leaf(node<T>* Node)
	{
		while (Node->left_child)
			Node = Node->left_child;
		return (Node);
	}
	node<T> *find_right_most_leaf(node<T>* Node)
	{
		while (Node->right_child)
			Node = Node->right_child;
		return (Node);
	}
	node<T> *sibling(node<T>* Node)
	{
		if (Node->parent == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (Node->parent->right_child);
		return (Node->parent->left_child);
	}
	node<T> *niece(node<T>* Node)
	{
		if (sibling(Node) == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (sibling(Node)->left_child);
		return (sibling(Node)->right_child);
	}
	node<T> *nephew(node<T>* Node)
	{
		if (sibling(Node) == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (sibling(Node)->right_child);
		return (sibling(Node)->left_child);
	}
	void	rotate_to_parent(node<T>* Node)
	{
		if (Node == Node->parent->left_child)
			right_rotate(Node->parent);
		else
			left_rotate(Node->parent);
	}
	node<T>	*has_one_child(node<T>* Node)
	{
		if (Node->left_child && Node->right_child == NULL)
			return (Node->left_child);
		if (Node->left_child == NULL && Node->right_child)
			return (Node->right_child);
		return (NULL);
	}
	node<T>	*make_node_leaf(node<T>* Node)
	{
		if (Node->left_child == NULL && Node->right_child == NULL)
			return (Node);
		if (has_one_child(Node))
		{
			ft::swap(Node->value, has_one_child(Node)->value);
			Node = has_one_child(Node);
			return (make_node_leaf(Node));
		}
		else
		{
			ft::swap(Node->value, get_predecessor(Node)->value);
			Node = get_predecessor(Node);
			return (make_node_leaf(Node));
		}
	}
	void	prune_leaf(node<T>* leaf)
	{
		if (leaf->parent)
		{
			if (leaf == leaf->parent->left_child)
				leaf->parent->left_child = NULL;
			else
				leaf->parent->right_child = NULL;
		}
		delete leaf;
	}

	// DEBUG
	void	print(const std::string& prefix, node<T>* x, bool isLeft) const
	{
		if (x)
		{
			std::cout << prefix;
			std::cout << (isLeft ? "├──" : "└──");
			std::cout << x->value << (x->color == BLACK ? " black" : " red" ) << std::endl;
			print(prefix + (isLeft ? "│   " : "    "), x->left_child, true);
			print(prefix + (isLeft ? "│   " : "    "), x->right_child, false);
		}
	}
};

} // ft

#endif
