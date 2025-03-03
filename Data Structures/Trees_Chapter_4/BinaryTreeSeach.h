#pragma once
#include <algorithm>
#include <iostream>

template<typename Object, typename Comparator = std::less<Object>>

class BinarySearchTree
{
public:
	struct BinaryNode;
	BinarySearchTree() {}
	BinarySearchTree(const BinarySearchTree& rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}
	BinarySearchTree( BinarySearchTree&& rhs ) {}

	~BinarySearchTree() { makeEmpty(); }

	BinarySearchTree& operator = (const BinarySearchTree& rhs) {}
	BinarySearchTree& operator = ( BinarySearchTree&& rhs) {}

public:

	const Object& findMin() const { return findMin(root)->element; }
	const Object& findMax() const { return findMax(root)->element; }

	const Object& getRoot() const { return retrieve(root); }

	BinaryNode* getRootNode() const { return root; }

	bool contains(const Object& x) { return contains(x, root); }
	bool isEmpty() {}

	void printTree(std::ostream& out = std::cout) { printTree(root, out); }

	void makeEmpty() 
	{
		makeEmpty(root);
	}

	void insert(const Object& x) { insert(x, root); }
	void insert(Object && x) { insert(std::move(x), root); }

	void remove(const Object& x) { remove(x, root); }


//private:
public:

	struct BinaryNode
	{
		Object element;
		BinaryNode* left;
		BinaryNode* right;

		BinaryNode(const Object& elm, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr) : element{ elm }, left{ lt }, right{ rt } {}

		BinaryNode( Object && elm, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr) : element{ std::move(elm) }, left{ lt }, right{ rt } {}
	};

private:

	void insert(const Object& x, BinaryNode*& t) 
	{
		if (t == nullptr)
			t = new BinaryNode(x, nullptr, nullptr);
		else if (isLessThan(x, t->element))
			insert(x, t->left);
		else if (isLessThan(t->element, x))
			insert(x, t->right);
		else std::cout << "Item already exists.\n";
	}
	void insert( Object&& x, BinaryNode * & t) 
	{
		if (t == nullptr)
			t = new BinaryNode(std::move(x), nullptr, nullptr);
		else if (isLessThan(x, t->element))
			insert(std::move(x), t->left);
		else if (isLessThan(t->element, x))
			insert(std::move(x), t->right);
		else std::cout << "Item already exists.\n";
	}

	bool contains (const Object& x, BinaryNode * t) const 
	{
		if (t == nullptr) return false;
		else if (isLessThan(x, t->element))
			contains(x, t->left);
		else if (isLessThan(t->element, x))
			contains(x, t->right);
		else return true;

	}

	void remove( const Object& x, BinaryNode *& t ) 
	{
		if (t == nullptr)
			return;
		else if (isLessThan(x, t->element))
			remove(x, t->left);
		else if (isLessThan(t->element, x))
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr)
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;

			delete oldNode;
		}

	}

	BinaryNode* findMin(BinaryNode* t) const 
	{
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;

		return findMin(t->left);
	}
	BinaryNode* findMax( BinaryNode* t ) const 
	{
		if (t != nullptr)
			while (t->right != nullptr)
			{
				t = t->right;
			}

		return t;
	}

	void makeEmpty(BinaryNode *& t) 
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		
		t = nullptr;
	}

	void printTree(BinaryNode* t, std::ostream& out ) const 
	{
		if (t == nullptr) return;

		out << t->element << "\n";

		printTree(t->left, out);

		printTree(t->right, out);
	}

	BinaryNode* clone(BinaryNode* t) const 
	{
		if (t == nullptr)
			return nullptr;

		else
		{
			return new BinaryNode{ t->element, clone(t->left), clone(t->right) };
		}
	}

	const Object& retrieve(BinaryNode* t) const { return t->element; }

private:
	BinaryNode* root;
	Comparator isLessThan;


};