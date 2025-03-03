#pragma once
#include <algorithm>


template<typename Object>
class Stack
{
public:

	explicit Stack(int initialSize = 0) : topOfStack{ -1 }, theCapacity{ initialSize + SPARE_CAPACITY }, collection{ nullptr }
	{
		collection = new Object[theCapacity];
	}

	Stack(const Stack& rhs) : topOfStack{ rhs.topOfStack }, theCapacity{ rhs.theCapacity }, collection{ nullptr } 
	{
		collection = new Object[theCapacity];

		for (int i = 0; i < topOfStack + 1; i++)
			collection[i] = rhs.collection[i];
	}

	Stack(Stack&& rhs) : topOfStack{ rhs.topOfStack }, theCapacity{ rhs.theCapacity }, collection{ rhs.collection }
	{
		rhs.topOfStack = -1;
		rhs.theCapacity = 0;
		rhs.collection = nullptr;
	}

	Stack& operator = (const Stack& rhs)
	{
		Stack copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	Stack& operator = (Stack&& rhs)
	{
		std::swap(topOfStack, rhs.topOfStack);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(collection, rhs.collection);

		return *this;
	}

	~Stack()
	{
		delete[] collection;
	}

	Object& operator[] (int index)
	{
		return collection[index];
	}



public:
	// reserve, pop, top, push_back, empty, size

	void reserve(int newCapacity)
	{
		if (newCapacity < topOfStack + 1)
			return;

		Object* newArray = new Object[newCapacity];

		for (int i = 0; i < topOfStack + 1; i++)
			newArray[i] = std::move(collection[i]);

		std::swap(collection, newArray);

		theCapacity = newCapacity;

		delete[] newArray;

	}

	void pop()
	{
		if (topOfStack < 0) return;
		--topOfStack;
	}
	Object& top() const
	{
		return collection[topOfStack];
	}
	void push_back(const Object& x)
	{
		if (topOfStack + 1 == theCapacity)
			reserve(2 * theCapacity + 1);

		collection[++topOfStack] = x;
	}
	void push_back(Object&& x)
	{
		if (topOfStack + 1 == theCapacity)
			reserve(2 * theCapacity + 1);

		collection[++topOfStack] = std::move(x);
	}

	int size() const { return topOfStack + 1; }

	bool empty() const { return size() == 0; }

public:

	static const int SPARE_CAPACITY = 16;
private:

	int topOfStack;
	int theCapacity;

	Object* collection;
};
