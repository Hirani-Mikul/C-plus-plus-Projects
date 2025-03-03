#pragma once
#include <algorithm>
#include <iostream>

template<typename Object>

class Stack {

public:

	explicit Stack(int initialSize = 0) : topOfStack{ -1 }, theCapacity{ initialSize + SPARE_CAPACITY }
	{
		objects = new Object[theCapacity];
	}

	Stack(const Stack& rhs) : topOfStack{ rhs.topOfStack }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
	{
		objects = new Object[ theCapacity ];
		for (int i = 0; i < topOfStack + 1; i++)
			objects[i] = rhs.objects[i];

	}

	Stack(Stack&& rhs) : topOfStack{ rhs.topOfStack }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.topOfStack = -1;
		rhs.theCapacity = 0;
		rhs.objects = nullptr;
	}

	Stack& operator = ( const Stack& rhs )
	{
		Stack copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	Stack& operator = (Stack && rhs)
	{
		std::swap(topOfStack, rhs.topOfStack);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	~Stack()
	{
		delete[] objects;
	}

public:

	Object& operator[] (int index) { return objects[index]; }	

	void reserve(int newCapacity)
	{
		if (newCapacity < topOfStack + 1)
			return;

		Object* newArray = new Object[newCapacity];

		for (int i = 0; i < topOfStack + 1; i++)
			newArray[i] = std::move(objects[i]);

		theCapacity = newCapacity;

		std::swap(objects, newArray);

		delete[] newArray;
	}

	Object& back()
	{
		if (empty()) std::cout << "Stack is empty.\n";
		//return objects[topOfStack--];
		return objects[topOfStack];
	}

	void push_back( const Object& rhs )
	{
		if (topOfStack + 1 == theCapacity)
			reserve(2 * theCapacity + 1);

		objects[++topOfStack] = rhs;
	}
	void push_back( Object&& rhs )
	{
		if (topOfStack + 1 == theCapacity)
			reserve(2 * theCapacity + 1);
		topOfStack++;
		objects[topOfStack] = std::move(rhs);
	}

	void pop_back()
	{
		topOfStack--;
	}

	int size() const { return topOfStack + 1; }

	bool empty() const{ return size() == 0; }

public:

	static const int SPARE_CAPACITY = 16;

private:

	int topOfStack;
	int theCapacity;

	Object* objects;

};