#pragma once
#include <algorithm>
#include <iostream>

//typedef int Object;
//typedef std::less<Object> Comparator;

template<typename Object, typename Comparator = std::less<Object>>

class AVL
{
private:
	struct AVLNode
	{
		Object element;
		AVLNode* left;
		AVLNode* right;

		int height;

		AVLNode(const Object& elm, AVLNode* lt = nullptr, AVLNode* rt = nullptr, int h = 0) : element{ elm }, left{ lt }, right{ rt }, height{ h }{}

		AVLNode(Object&& elm, AVLNode* lt = nullptr, AVLNode* rt = nullptr, int h = 0) : element{ std::move(elm) }, left{ lt }, right{ rt }, height{ h } {}
	};

public:

	AVL() {}
	AVL(const AVL& rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}
	AVL(AVL&& rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	~AVL() { makeEmpty(); }

	AVL& operator = (const AVL& rhs)
	{
		AVL copy = rhs;
		std::swap(*this, copy);
		return *this;

	}
	AVL& operator = (AVL&& rhs)
	{
		std::swap(root, rhs.root);

		return *this;
	}

public:

	void insert(const Object& x) { insert(x, root); }
	void insert(Object&& x) { insert(std::move(x), root); }
	void remove(const Object& x) { remove(x, root); }

	auto findMin() { return findMin(root); }
	auto findMax() { return findMax(root); }

	void makeEmpty() 
	{
		makeEmpty(root);
	}

	int getTreeHeight() const { return height(root); }

	int height(AVLNode* t) const { return t == nullptr ? -1 : t->height; }

	void printTree() const { printTree(root); }

private:

	void rotateWithLeftChild ( AVLNode *& k2 ) 
	{
		AVLNode* k1 = k2->left;

		k2->left = k1->right;
		k1->right = k2;

		k2->height = std::max( height(k2->left), height(k2->right) ) + 1;
		k1->height = std::max( height(k1->left), k2->height ) + 1;

		k2 = k1;

	}
	void rotateWithRightChild( AVLNode *& k2 ) 
	{
		AVLNode* k1 = k2->right;

		k2->right = k1->left;
		k1->left = k2;

		k2->height = std::max(height(k2->left), height(k2->right)) + 1;
		k1->height = std::max(height(k1->left), k2->height) + 1;

		k2 = k1;

	}
	void doubleWithLeftChild ( AVLNode *& k3 ) 
	{
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}
	void doubleWithRightChild( AVLNode *& k3 ) 
	{
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}

	void balance( AVLNode *& t ) 
	{
		if (t == nullptr) return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
		{
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else doubleWithLeftChild(t);
		}
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
		{
			if (height(t->right->right) >= height(t->right->left))
				rotateWithRightChild(t);
			else doubleWithRightChild(t);
		}

		t->height = std::max( height(t->left), height(t->right) ) + 1;
	}

	void insert(const Object& x, AVLNode*& t) 
	{
		if (t == nullptr) t = new AVLNode{ x };
		else if (isLessThan(x, t->element)) insert(x, t->left);
		else if (isLessThan(t->element, x)) insert(x, t->right);
		else return;

		balance(t);
	}
	void insert(Object&& x, AVLNode*& t) 
	{
		if (t == nullptr) t = new AVLNode{ std::move(x) };
		else if (isLessThan(x, t->element)) insert(std::move(x), t->left);
		else if (isLessThan(t->element, x)) insert(std::move(x), t->right);
		else return;

		balance(t);
	}
	void remove(const Object& x, AVLNode*& t) 
	{ 
		if (t == nullptr) return;

		if (x < t->element) remove(x, t->left);
		else if (x > t->element) remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			AVLNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;

			delete oldNode;
		}

		balance(t);
	}

	AVLNode* findMin(AVLNode* t) const 
	{
		if (t == nullptr) return nullptr;
		else if (t->left == nullptr) return t;
		
		return findMin(t->left);
	}
	AVLNode* findMax(AVLNode* t) const 
	{
		if (t != nullptr)
			while (t->right != nullptr)
			{
				t = t->right;
			}

		return t;
	}

	bool contains(const Object& x, AVLNode* t) const
	{
		if (t == nullptr) return false;
		else if (isLessThan(x, t->element))
			contains(x, t->left);
		else if (isLessThan(t->element, x))
			contains(x, t->right);
		else return true;

	}

	AVLNode* clone(AVLNode* t) const
	{
		if (t == nullptr) return nullptr;
		else return new AVLNode(t->element, clone(t->left), clone(t->right));
	}

	void makeEmpty(AVLNode *& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}

		t = nullptr;
	}

	void printTree( AVLNode* t, int space = 5, std::ostream& out = std::cout ) const
	{
		if (t == nullptr) return;
		space += 5;
		printTree(t->right, space);

		out << "\n";

		for (int i = 5; i < space; i++) out << " ";

		out << t->element << "\n";

		printTree(t->left, space);
	}

	static const int ALLOWED_IMBALANCE = 1;

private:
	AVLNode* root;
	Comparator isLessThan;
};