#include <iostream>
#include "BTree.h"

int main(void)
{
	BTree<int> tree = {};
	try {
		BTree<int> temp({ 0, 1, 2, 3, 4, 5, 6 }, { true, true, true, true, true, true, true });

		tree = temp; 
	}
	catch (MissingTreeNode& e) {
		e.what(); 
	}

	tree.print(0);
	tree.print(1);
	tree.print(2);
	tree.print(3);

	return 0; 
}