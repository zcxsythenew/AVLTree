#pragma once
#include "Binary_tree.h"
#include "Record.h"

template <class Key, class Entry>
class Search_tree : public Binary_tree<Record<Key, Entry>>
{
public:
	bool insert(const Record<Key, Entry> &data)
	{
		return recursive_tree_insert(this->root, data);
	}

	bool remove(const Record<Key, Entry> &data)
	{
		Binary_node<Record<Key, Entry>> *found = recursive_tree_search(this->root, data);
		if (found != nullptr)
		{
			remove_node(found);
		}
		return found != nullptr;
	}

	bool tree_search(Record<Key, Entry> &target)
	{
		Binary_node<Record<Key, Entry>> *found = recursive_tree_search(this->root, target);
		if (found != nullptr) target = found->data;
		return found != nullptr;
	}

protected:
	Binary_node<Record<Key, Entry>> *recursive_tree_search(Binary_node<Record<Key, Entry>> *this_root, const Record<Key, Entry> &target)
	{
		while (this_root != nullptr)
		{
			if ((Key)(this_root->data) < (Key)(target))
			{
				this_root = this_root->right;
				continue;
			}

			if ((Key)(target) < (Key)(this_root->data))
			{
				this_root = this_root->left;
				continue;
			}

			return this_root;
		}

		return this_root;
	}

	bool recursive_tree_insert(Binary_node<Record<Key, Entry>> *&this_root, const Record<Key, Entry> &data)
	{
		if (this_root == nullptr)
		{
			this_root = new Binary_node<Record<Key, Entry>>{ data, nullptr, nullptr };
			this->_size++;
			return true;
		}

		if ((Key)(this_root->data) < (Key)(data))
		{
			return recursive_tree_insert(this_root->right, data);
		}

		if ((Key)(data) < (Key)(this_root->data))
		{
			return recursive_tree_insert(this_root->left, data);
		}

		return false;
	}

	bool remove_node(Binary_node<Record<Key, Entry>> *&this_root)
	{
		if (this_root != nullptr)
		{
			if (this_root->left == nullptr && this_root->right == nullptr)
			{
				delete this_root;
				this_root = nullptr;
			}
			else if (this_root->left == nullptr)
			{
				delete this_root;
				this_root = this_root->right;
			}
			else if (this_root->right == nullptr)
			{
				delete this_root;
				this_root = this_root->left;
			}
			else
			{
				Binary_node<Record<Key, Entry>> *i, *parent = this_root;
				for (i = this_root->left; i->right != nullptr; i = i->right)
				{
					parent = i;
				}
				this_root->data = i->data;
				if (parent->left == i) parent->left = nullptr;
				if (parent->right == i) parent->right = nullptr;
				delete i;
			}
			this->_size--;
			return true;
		}
		else
		{
			return false;
		}
	}
};