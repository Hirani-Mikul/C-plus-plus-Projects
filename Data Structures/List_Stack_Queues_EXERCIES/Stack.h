#pragma once
#include <algorithm>

template<typename Object>

class Stack
{
public:
	explicit Stack(size_t initialCapacity = 0) : topOfStack(-1), theCapacity{ initialCapacity + SPARE_CAPACITY } 
	{
		objects = new Object[theCapacity];
	}

	Stack(const Stack& rhs) : topOfStack{ rhs.topOfStack }, theCapacity{ rhs.theCapacity }, objects{ nullptr } 
	{
		objects = new Object[theCapacity];
		for (int i = 0; i < topOfStack; i++)
			objects[i] = rhs.objects[i];
	}

	Stack(Stack && rhs) : topOfStack{ rhs.topOfStack }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
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
	Stack& operator = (Stack&& rhs)
	{
		std::swap(topOfStack, rhs.topOfStack);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	~Stack()
	{
		topOfStack = -1;
		delete[] objects;
		//clear();
		//::operator delete(objects, theCapacity * sizeof(Object));
	}

public:
	void reserve(size_t newCapacity)
	{
		Object* newArr = (Object*)::operator new(newCapacity * sizeof(Object));

		for (int i = 0; i < topOfStack; i++)
		{
			new(&newArr[i]) Object(std::move(objects[i]));
		}

		for (int i = 0; i < topOfStack; i++)
			objects[i].~Object();

		::operator delete(objects, theCapacity * sizeof(Object));

		objects = newArr;
		theCapacity = newCapacity;
	}

public:

	Object& operator[] (int index) { return objects[index]; }


	void push_back(const Object& rhs)
	{
		if (topOfStack + 1 == theCapacity)
			reserve(2 * theCapacity + 1);

		objects[++topOfStack] = rhs;
	}
	void push_back(Object&& rhs)
	{
		if (topOfStack + 1 == theCapacity)
			reserve(2 * theCapacity + 1);
		topOfStack++;
		objects[topOfStack] = std::move(rhs);
	}

	Object& top() const { return objects[topOfStack]; }
	Object& pop() 
	{
		return objects[topOfStack--];
	}

	int size() const { return topOfStack + 1; }
	size_t capacity() const { return theCapacity; }
	bool empty() const { return size() == 0; }

	void clear()
	{
		for (int i = 0; i < topOfStack; i++)
			objects[i].~Object();

		topOfStack = -1;
	}

public:

	static const size_t SPARE_CAPACITY = 5;

private:

	int topOfStack;
	size_t theCapacity;

	Object* objects;
};