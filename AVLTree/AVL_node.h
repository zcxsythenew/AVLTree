#pragma once
#include "Balance_factor.h"
#include "Binary_node.h"
#include "Record.h"

template <class Key, class Entry>
struct AVL_node : public Binary_node<Record<Key, Entry>>
{
	Record<Key, Entry> data;
	AVL_node *left;
	AVL_node *right;
	Balance_factor balance;
};