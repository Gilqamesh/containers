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
# include "utility.hpp"

// DEBUG
# include <string>
# include <iostream>

namespace ft
{

template <typename Key, typename Value, class Compare = ft::less<Value>, class Allocator = ft::pair<const Key, Value> >
class red_black_tree
{
private:
	enum color_type
	{
		BLACK,
		RED
	};
public:
	template <typename K, typename V>
	class node
	{
	friend class red_black_tree;
	public:
		node()
			: key(), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
		node(const K& k, const V& v)
			: key(k), value(v), color(RED), left_child(NULL), right_child(NULL), parent(NULL) { }
		node(const node& other)
			: key(other.key), value(other.value), color(other.color), left_child(other.left_child), right_child(other.right_child), parent(other.parent) { }
		node &operator=(const node& other)
		{
			if (this != &other)
			{
				key = other.key;
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
		K 			key;
		V			value;
		color_type	color;
		node*		left_child;
		node*		right_child;
		node*		parent;
	};

	red_black_tree()
		: root(NULL) { }
	~red_black_tree() { delete_from_node(root); }

	node<Key, Value>	*search(const Key& key) { return (search(key, root)); }
	void 				insert(const Key& key, const Value& value)
	{
		node<Key, Value>* z = new node<Key, Value>(key, value);
		node<Key, Value>* y = NULL;
		node<Key, Value>* x = root;
		while (x != NULL)
		{
			y = x;
			if (Compare()(z->key, x->key))
				x = x->left_child;
			else
				x = x->right_child;
		}
		z->parent = y;
		if (y == NULL)
			root = z;
		else if (z->key < y->key)
			y->left_child = z;
		else
			y->right_child = z;
		insert_fixup(z);
	}
	void				remove(const Key& key)
	{
		node<Key, Value>*	Node = search(key);
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
	node<Key, Value>*	root;

	node<Key, Value> *search(const Key& key, node<Key, Value> *x)
	{
		if (x == NULL)
			return (NULL);
		if (key == x->key)
			return (x);
		if (Compare()(key, x->key))
			return (search(key, x->left_child));
		else
			return (search(key, x->right_child));
	}
	void insert_fixup(node<Key, Value>* z)
	{
		while (z != root && z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->left_child)
			{
				node<Key, Value>*	y = z->parent->parent->right_child; // z's uncle
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
				node<Key, Value>*	y = z->parent->parent->left_child;
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
	void left_rotate(node<Key, Value>* x)
	{
		node<Key, Value>*	y = x->right_child;
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
	void right_rotate(node<Key, Value> *x)
	{
		node<Key, Value>*	y = x->left_child;
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
	void delete_from_node(node<Key, Value>* x)
	{
		if (x == NULL)
			return ;
		if (x->left_child)
			delete_from_node(x->left_child);
		if (x->right_child)
			delete_from_node(x->right_child);
		delete x;
	}
	void delete_fixup(node<Key, Value>* x)
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
	node<Key, Value> *get_successor(node<Key, Value>* Node)
	{
		if (Node->right_child)
			return (find_left_most_leaf(Node->right_child));
		
		node<Key, Value>*	p = Node->parent;
		while (p && Node == p->right_child)
		{
			Node = p;
			p = p->parent;
		}
		return (p);
	}
	node<Key, Value> *get_predecessor(node<Key, Value> *Node)
	{
		if (Node->left_child)
			return (find_right_most_leaf(Node->left_child));
		
		node<Key, Value>*	p = Node->parent;
		while (p && Node == p->left_child)
		{
			Node = p;
			p = p->parent;
		}
		return (p);
	}
	node<Key, Value> *find_left_most_leaf(node<Key, Value>* Node)
	{
		while (Node->left_child)
			Node = Node->left_child;
		return (Node);
	}
	node<Key, Value> *find_right_most_leaf(node<Key, Value>* Node)
	{
		while (Node->right_child)
			Node = Node->right_child;
		return (Node);
	}
	node<Key, Value> *sibling(node<Key, Value>* Node)
	{
		if (Node->parent == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (Node->parent->right_child);
		return (Node->parent->left_child);
	}
	node<Key, Value> *niece(node<Key, Value>* Node)
	{
		if (sibling(Node) == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (sibling(Node)->left_child);
		return (sibling(Node)->right_child);
	}
	node<Key, Value> *nephew(node<Key, Value>* Node)
	{
		if (sibling(Node) == NULL)
			return (NULL);
		if (Node == Node->parent->left_child)
			return (sibling(Node)->right_child);
		return (sibling(Node)->left_child);
	}
	void	rotate_to_parent(node<Key, Value>* Node)
	{
		if (Node == Node->parent->left_child)
			right_rotate(Node->parent);
		else
			left_rotate(Node->parent);
	}
	node<Key, Value>	*has_one_child(node<Key, Value>* Node)
	{
		if (Node->left_child && Node->right_child == NULL)
			return (Node->left_child);
		if (Node->left_child == NULL && Node->right_child)
			return (Node->right_child);
		return (NULL);
	}
	node<Key, Value>	*make_node_leaf(node<Key, Value>* Node)
	{
		if (Node->left_child == NULL && Node->right_child == NULL)
			return (Node);
		if (has_one_child(Node))
		{
			ft::swap(Node->key, has_one_child(Node)->key);
			ft::swap(Node->value, has_one_child(Node)->value);
			Node = has_one_child(Node);
			return (make_node_leaf(Node));
		}
		else
		{
			ft::swap(Node->key, get_predecessor(Node)->key);
			ft::swap(Node->value, get_predecessor(Node)->value);
			Node = get_predecessor(Node);
			return (make_node_leaf(Node));
		}
	}
	void	prune_leaf(node<Key, Value>* leaf)
	{
		if (leaf->parent)
		{
			if (leaf == leaf->parent->left_child)
				leaf->parent->left_child = NULL;
			else
				leaf->parent->right_child = NULL;
		}
		std::cout << "Removing " << leaf->key << std::endl;
		delete leaf;
	}

	// DEBUG
	void	print(const std::string& prefix, node<Key, Value>* x, bool isLeft) const
	{
		if (x)
		{
			std::cout << prefix;
			std::cout << (isLeft ? "├──" : "└──");
			std::cout << x->key << (x->color == BLACK ? " black" : " red" ) << std::endl;
			print(prefix + (isLeft ? "│   " : "    "), x->left_child, true);
			print(prefix + (isLeft ? "│   " : "    "), x->right_child, false);
		}
	}
};

} // ft

#endif
