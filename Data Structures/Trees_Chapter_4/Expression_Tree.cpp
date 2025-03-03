//#include <iostream>
//#include <queue>
//#include <stack>
//#include <string>
//#include <algorithm>
//
//#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
//#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';
//
//template<typename Object>
//struct BinaryNode
//{
//	Object element;
//
//	BinaryNode* left;
//	BinaryNode* right;
//};
//
//template<typename Object>
//BinaryNode<Object>* createNode(Object key)
//{
//	BinaryNode<Object>* node = new BinaryNode<Object>();
//	node->element = key;
//	node->left = nullptr;
//	node->right = nullptr;
//
//	return node;
//}
//
//template<typename Object>
//BinaryNode<Object>* search(BinaryNode<Object>* root, Object key)
//{
//	if (root == nullptr)
//		return nullptr;
//
//	std::queue<BinaryNode<Object>*> q;
//
//	BinaryNode<Object>* out = nullptr;
//
//	q.push(root);
//
//	while (!q.empty())
//	{
//		BinaryNode<Object>* temp = q.front();
//		q.pop();
//
//		if (temp->element == key) out = temp;
//		if (temp->left != nullptr) q.push(temp->left);
//		if (temp->right != nullptr) q.push(temp->right);
//
//	}
//
//	return out;
//}
//
//template<typename Object>
//void printTree(BinaryNode<Object>* root)
//{
//	if (root == nullptr)
//		return;
//
//	std::queue<BinaryNode<Object>*> q;
//
//	q.push(root);
//
//	while (!q.empty())
//	{
//		BinaryNode<Object>* temp = q.front();
//		q.pop();
//
//		std::cout << temp->element << "\n";
//
//		if (temp->left != nullptr) q.push(temp->left);
//		if (temp->right != nullptr) q.push(temp->right);
//
//	}
//
//}
//
//template<typename Object>
//void recursive_printTree(BinaryNode<Object>* node)
//{
//	if (node == nullptr) return;
//
//	std::cout << node->element << "\n";
//
//	recursive_printTree(node->left);
//
//	recursive_printTree(node->right);
//}
//
//int main()
//{
//	
//	std::string postfix_exp = "ab+cde+**";
//
//	std::string delimeter = "*/+-";
//
//	std::stack<BinaryNode<char>*> s;
//
//	for (auto i = postfix_exp.begin(); i != postfix_exp.end(); i++)
//	{
//		if (std::find(delimeter.begin(), delimeter.end(), *i) == delimeter.end())
//		{
//			BinaryNode<char>* p = createNode(*i);
//			s.push(p);
//
//		}
//		else
//		{
//			//if (s.size() > 1)
//			//{
//				BinaryNode<char>* t1 = s.top();
//				s.pop();
//				BinaryNode<char>* t2 = s.top();
//				s.pop();
//
//				BinaryNode<char>* root = createNode(*i);
//				root->left = t2;
//				root->right = t1;
//
//				s.push(root);
//
//			//}
//		}
//
//	}
//
//	//std::cout << s.size() << "\n";
//
//	//printTree(s.top());
//	recursive_printTree(s.top());
//
//	_New(2);
//	_Wait();
//	return 0;
//}