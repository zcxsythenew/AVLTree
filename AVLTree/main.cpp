#include "AVL_tree.h"
#include <iostream>

using namespace std;

int main()
{
	AVL_tree<char, char> tree;
	const char *str = "mepcjnsbdhkoruagiltf";
	for (int i = 0; str[i] != '\0'; i++)
	{
		tree.insert(Record<char, char> {str[i], str[i]});
	}
	tree.remove(Record<char, char> {'p', 'p'});

	tree.inorder([](Record<char, char> &d) -> void { cout << d << ' '; });
	cout << endl;

	tree.preorder([](Record<char, char> &d) -> void { cout << d << ' '; });
	cout << endl;

	tree.postorder([](Record<char, char> &d) -> void { cout << d << ' '; });
	cout << endl;

	return 0;
}