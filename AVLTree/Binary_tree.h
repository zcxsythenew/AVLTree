#pragma once
#include "Binary_node.h"

template <class Entry>
class Binary_tree
{
public:
	Binary_tree() : root(nullptr), _size(0)
	{

	}

	bool empty() const noexcept
	{
		return root == nullptr;
	}

	void inorder(void(*visit)(Entry &))
	{
		recursive_inorder(visit, root);
	}

	void preorder(void(*visit)(Entry &))
	{
		recursive_preorder(visit, root);
	}

	void postorder(void(*visit)(Entry &))
	{
		recursive_postorder(visit, root);
	}

	int size() const noexcept
	{
		return _size;
	}

	void clear()
	{
		recursive_clear(root);
	}

	virtual ~Binary_tree()
	{
		clear();
	}

protected:
	Binary_node<Entry> *root;
	int _size;

	void recursive_inorder(void(*visit)(Entry &), Binary_node<Entry> *this_root)
	{
		if (this_root != nullptr)
		{
			recursive_inorder(visit, this_root->left);
			(*visit)(this_root->data);
			recursive_inorder(visit, this_root->right);
		}
	}

	void recursive_preorder(void(*visit)(Entry &), Binary_node<Entry> *this_root)
	{
		if (this_root != nullptr)
		{
			(*visit)(this_root->data);
			recursive_preorder(visit, this_root->left);
			recursive_preorder(visit, this_root->right);
		}
	}

	void recursive_postorder(void(*visit)(Entry &), Binary_node<Entry> *this_root)
	{
		if (this_root != nullptr)
		{
			recursive_postorder(visit, this_root->left);
			recursive_postorder(visit, this_root->right);
			(*visit)(this_root->data);
		}
	}

	void recursive_clear(Binary_node<Entry> *&this_root)
	{
		if (this_root != nullptr)
		{
			recursive_clear(this_root->left);
			recursive_clear(this_root->right);
			delete this_root;
			this_root = nullptr;
		}
	}
};