#include <iostream>
#include <queue>

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';

template<typename Object>
struct BinaryNode
{
	Object element;

	BinaryNode* left;
	BinaryNode* right;
};

template<typename Object>
BinaryNode<Object>* createNode( Object key )
{
	BinaryNode<Object> *node = new BinaryNode<Object>();
	node->element = key;
	node->left  = nullptr;
	node->right = nullptr;

	return node;
}

template<typename Object>
BinaryNode<Object>* search(BinaryNode<Object> *root, Object key)
{
	if (root == nullptr)
		return nullptr;

	std::queue<BinaryNode<Object>*> q;

	BinaryNode<Object>* out = nullptr;

	q.push(root);

	while (!q.empty())
	{
		BinaryNode<Object>* temp = q.front();
		q.pop();

		if (temp->element == key) out = temp;
		if (temp->left != nullptr) q.push(temp->left);
		if (temp->right != nullptr) q.push(temp->right);

	}

	return out;
}

template<typename Object>
void printTree(BinaryNode<Object>* root)
{
	if (root == nullptr)
		return;

	std::queue<BinaryNode<Object>*> q;

	q.push(root);

	while (!q.empty())
	{
		BinaryNode<Object>* temp = q.front();
		q.pop();

		std::cout << temp->element << "\n";

		if (temp->left != nullptr) q.push(temp->left);
		if (temp->right != nullptr) q.push(temp->right);

	}

}

int BT_EG_1()
{
	BinaryNode<int>* root = createNode(1);
	root->left = createNode(2);
	root->right = createNode(3);

	root->left->left = createNode(4);
	root->left->right = createNode(5);

	root->right->left = createNode(6);
	root->right->right = createNode(7);

	BinaryNode<int>* res = search(root, 5);

	if (res != nullptr)
	{
		std::cout << "Found result: " << res->element << "\n";
	}
	else std::cout << "Key not found.\n";

	_New(2);

	printTree(root);

	_New(2);
	_Wait();
	return 0;
}