#pragma once
#include "Search_tree.h"
#include "AVL_node.h"

template <class Key, class Entry>
class AVL_tree// : public Search_tree<Key, Entry>
{
public:
	AVL_tree() : root(nullptr), _size(0)
	{

	}

	bool empty() const noexcept
	{
		return root == nullptr;
	}

	void inorder(void(*visit)(Record<Key, Entry> &))
	{
		recursive_inorder(visit, root);
	}

	void preorder(void(*visit)(Record<Key, Entry> &))
	{
		recursive_preorder(visit, root);
	}

	void postorder(void(*visit)(Record<Key, Entry> &))
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

	virtual ~AVL_tree()
	{
		clear();
	}

	bool insert(const Record<Key, Entry> &data)
	{
		bool taller;
		return recursive_tree_insert(this->root, data, taller);
	}

	bool remove(const Record<Key, Entry> &data)
	{
		bool shorter;
		return recursive_tree_remove(root, data, shorter);
	}

protected:
	AVL_node<Key, Entry> *root;
	int _size;

	AVL_node<Key, Entry> *recursive_tree_search(AVL_node<Key, Entry> *this_root, const Record<Key, Entry> &target)
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

	bool remove_node(AVL_node<Key, Entry> *&this_root, bool &shorter)
	{
		if (this_root != nullptr)
		{
			if (this_root->left == nullptr && this_root->right == nullptr)
			{
				delete this_root;
				this_root = nullptr;
				shorter = true;
			}
			else if (this_root->left == nullptr)
			{
				delete this_root;
				this_root = this_root->right;
				shorter = true;
			}
			else if (this_root->right == nullptr)
			{
				delete this_root;
				this_root = this_root->left;
				shorter = true;
			}
			else
			{
				AVL_node<Key, Entry> *i;
				for (i = this_root->left; i->right != nullptr; i = i->right);
				this_root->data = i->data;
				AVL_remove(this_root->left, shorter);
			}
			if (shorter)
			{
				switch (this_root->balance)
				{
				case left_higher:
					this_root->balance = equal_height;
					break;

				case equal_height:
					this_root->balance = right_higher;
					shorter = false;
					break;

				case right_higher:
					if (this_root->right->balance == equal_height)
					{
						shorter = false;
					}
					right_balance(this_root);
					break;
				}
			}
			this->_size--;
			return true;
		}
		else
		{
			return false;
		}
	}

	Record<Key, Entry> AVL_remove(AVL_node<Key, Entry> *&this_root, bool &shorter)
	{
		if (this_root->right != nullptr)
		{
			Record<Key, Entry> ent = AVL_remove(this_root->right, shorter);
			if (shorter)
			{
				switch (this_root->balance)
				{
				case left_higher:
					left_balance(this_root);
					if (this_root->left->balance == equal_height)
					{
						shorter = false;
					}
					break;

				case equal_height:
					this_root->balance = left_higher;
					shorter = false;
					break;

				case right_higher:
					this_root->balance = equal_height;
					break;
				}
			}
			return ent;
		}
		else
		{
			shorter = true;
			Record<Key, Entry> ent = this_root->data;
			delete this_root;
			this_root = nullptr;
			return ent;
		}
	}

	void recursive_inorder(void(*visit)(Record<Key, Entry> &), AVL_node<Key, Entry> *this_root)
	{
		if (this_root != nullptr)
		{
			recursive_inorder(visit, this_root->left);
			(*visit)(this_root->data);
			recursive_inorder(visit, this_root->right);
		}
	}

	void recursive_preorder(void(*visit)(Record<Key, Entry> &), AVL_node<Key, Entry> *this_root)
	{
		if (this_root != nullptr)
		{
			(*visit)(this_root->data);
			recursive_preorder(visit, this_root->left);
			recursive_preorder(visit, this_root->right);
		}
	}

	void recursive_postorder(void(*visit)(Record<Key, Entry> &), AVL_node<Key, Entry> *this_root)
	{
		if (this_root != nullptr)
		{
			recursive_postorder(visit, this_root->left);
			recursive_postorder(visit, this_root->right);
			(*visit)(this_root->data);
		}
	}

	void recursive_clear(AVL_node<Key, Entry> *&this_root)
	{
		if (this_root != nullptr)
		{
			recursive_clear(this_root->left);
			recursive_clear(this_root->right);
			delete this_root;
			this_root = nullptr;
		}
	}

	bool recursive_tree_remove(AVL_node<Key, Entry> *&this_root, const Record<Key, Entry> &target, bool &shorter)
	{
		if (this_root == nullptr)
		{
			return false;
		}
		else
		{
			if ((Key)(this_root->data) < (Key)(target))
			{
				bool result = recursive_tree_remove(this_root->right, target, shorter);
				if (result && shorter)
				{
					switch (this_root->balance)
					{
					case left_higher:
						if (this_root->left->balance == equal_height)
						{
							shorter = false;
						}
						left_balance(this_root);
						break;

					case equal_height:
						this_root->balance = left_higher;
						shorter = false;
						break;

					case right_higher:
						this_root->balance = equal_height;
						break;
					}
				}
				return result;
			}

			if ((Key)(target) < (Key)(this_root->data))
			{
				bool result = recursive_tree_remove(this_root->left, target, shorter);
				if (result && shorter)
				{
					switch (this_root->balance)
					{
					case left_higher:
						this_root->balance = equal_height;
						break;

					case equal_height:
						this_root->balance = right_higher;
						shorter = false;
						break;

					case right_higher:
						if (this_root->right->balance == equal_height)
						{
							shorter = false;
						}
						right_balance(this_root);
						break;
					}
				}
				return result;
			}

			remove_node(this_root, shorter);
			return true;
		}
	}

	bool recursive_tree_insert(AVL_node<Key, Entry> *&this_root, const Record<Key, Entry> &data, bool &taller)
	{
		if (this_root == nullptr)
		{
			this_root = new AVL_node<Key, Entry>();
			this_root->data = data;
			this_root->left = nullptr;
			this_root->right = nullptr;
			this_root->balance = equal_height;
			taller = true;
			this->_size++;
			return true;
		}

		if ((Key)(this_root->data) < (Key)(data))
		{
			bool result = recursive_tree_insert(this_root->right, data, taller);
			if (result && taller)
			{
				switch (this_root->balance)
				{
				case left_higher:
					this_root->balance = equal_height;
					taller = false;
					break;

				case equal_height:
					this_root->balance = right_higher;
					break;

				case right_higher:
					right_balance(this_root);
					taller = false;
					break;
				}
			}
			return result;
		}

		if ((Key)(data) < (Key)(this_root->data))
		{
			bool result = recursive_tree_insert(this_root->left, data, taller);
			if (result && taller)
			{
				switch (this_root->balance)
				{
				case left_higher:
					left_balance(this_root);
					taller = false;
					break;

				case equal_height:
					this_root->balance = left_higher;
					break;

				case right_higher:
					this_root->balance = equal_height;
					taller = false;
					break;
				}
			}
			return result;
		}

		taller = false;
		return false;
	}

	void right_balance(AVL_node<Key, Entry> *&this_root)
	{
		AVL_node<Key, Entry> *right_tree = this_root->right;
		AVL_node<Key, Entry> *root = this_root;
		if (this_root->right->balance != left_higher)
		{
			this_root->right = this_root->right->left;
			right_tree->left = this_root;
			this_root = right_tree;

			root->balance = equal_height;
			right_tree->balance = equal_height;
		}
		else
		{
			AVL_node<Key, Entry> *sub_tree = this_root->right->left;
			root->right = sub_tree->left;
			right_tree->left = sub_tree->right;
			sub_tree->left = this_root;
			sub_tree->right = right_tree;
			this_root = sub_tree;

			sub_tree->balance = equal_height;
			if (sub_tree->balance == left_higher)
			{
				root->balance = equal_height;
				right_tree->balance = right_higher;
			}
			else
			{
				root->balance = left_higher;
				right_tree->balance = equal_height;
			}
		}
	}

	void left_balance(AVL_node<Key, Entry> *&this_root)
	{
		AVL_node<Key, Entry> *left_tree = this_root->left;
		AVL_node<Key, Entry> *root = this_root;
		if (this_root->left->balance != right_higher)
		{
			this_root->left = this_root->left->right;
			left_tree->right = this_root;
			this_root = left_tree;

			root->balance = equal_height;
			left_tree->balance = equal_height;
		}
		else
		{
			AVL_node<Key, Entry> *sub_tree = this_root->left->right;
			root->left = sub_tree->right;
			left_tree->right = sub_tree->left;
			sub_tree->right = this_root;
			sub_tree->left = left_tree;
			this_root = sub_tree;

			sub_tree->balance = equal_height;
			if (sub_tree->balance == right_higher)
			{
				root->balance = equal_height;
				left_tree->balance = left_higher;
			}
			else
			{
				root->balance = right_higher;
				left_tree->balance = equal_height;
			}
		}
	}
};