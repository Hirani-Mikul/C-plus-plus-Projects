#include <iostream>
#include "BinaryTreeSeach.h"

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';

#define GLOBAL_SPACE 5

void printTree(BinarySearchTree<int>::BinaryNode* root, int space)
{
	if (root == nullptr) return;
	space += GLOBAL_SPACE;
	printTree(root->right, space);

	std::cout << "\n";

	for (int i = GLOBAL_SPACE; i < space; i++) std::cout << " ";

	std::cout << root->element << "\n";

	printTree(root->left, space);
}

int PrintingBST()
{
	BinarySearchTree<int> num;

	num.insert(100);
	num.insert(50);
	num.insert(150);

	num.insert(150);
	num.insert(120);
	num.insert(180);
	num.insert(122);

	num.insert(900);

	num.insert(30);
	num.insert(90);

	num.insert(85);
	num.insert(92);

	num.insert(15);
	num.insert(40);
	num.insert(10);
	num.insert(25);
	num.insert(2);
	num.insert(12);

	num.insert(5);
	num.insert(28);

	num.insert(26);
	num.insert(51);



	//std::cout << "Min: " << num.findMin() << "\n";
	//std::cout << "Max: " << num.findMax() << "\n";

	//num.remove(3);

	//std::cout << "Root element: " << num.getRoot() << "\n";

	//num.printTree();

	auto root = num.getRootNode();

	printTree(root, 5);

	_New(3);
	_Wait();
	return 0;
}