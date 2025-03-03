#include <iostream>
#include "AVL_Tree.h"

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';

#define GLOBAL_SPACE 5

//void printTree(AVL<int>::AVLNode* root, int space)
//{
//	if (root == nullptr) return;
//	space += GLOBAL_SPACE;
//	printTree(root->right, space);
//
//	std::cout << "\n";
//
//	for (int i = GLOBAL_SPACE; i < space; i++) std::cout << " ";
//
//	std::cout << root->element << "\n";
//
//	printTree(root->left, space);
//}

int main()
{
	AVL<int> avl;

	avl.insert(1);
	avl.insert(2);
	avl.insert(3);
	avl.insert(4);
	avl.insert(5);
	avl.insert(6);

	avl.remove(4);
	//avl.insert(5);
	//avl.insert(6);
	//avl.insert(7);
	//avl.insert(10);

	std::cout << "Height: " << avl.getTreeHeight() << "\n";
	std::cout << "Min: " << avl.findMin()->element << "\n";
	std::cout << "Max: " << avl.findMax()->element << "\n";

	_New(3);

	avl.printTree();

	_New(2);
	_Wait();
	return 0;
}