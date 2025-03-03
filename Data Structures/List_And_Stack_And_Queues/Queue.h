#pragma once
#include <algorithm>
#include <iostream>

template<typename Object>

class Queue
{
public:

	explicit Queue(int initialSize = 0) : theSize{ initialSize }, theCapacity{ initialSize + SPARE_SPACE }, objects{ nullptr }, front{ -1 }, rear{ -1 }
	{
		objects = new Object[theCapacity];
	}

	explicit Queue(const Queue& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, front{ rhs.front }, rear{ rhs.rear }, objects{ nullptr }
	{
		objects = new Object[theCapacity];

		for (int i = 0; i < theSize; i++)
			objects[i] = rhs.objects[i];
	}

	explicit Queue(Queue&& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }, front{ rhs.front }, rear{ rhs.rear }
	{

		rhs.objects = nullptr;
		rhs.front = -1;
		rhs.rear = -1;
		rhs.theCapacity = 0;
		rhs.theSize = 0;

	}


public:

	void enqueue(const Object& x)
	{
		theSize++;
		objects[++rear] = x;
	}
	void enqueue(Object&& x)
	{
		rear++;
		if (theSize == theCapacity)
		{
			std::cout << "Queue is full.\n";
			return;
		}
		if (rear == theCapacity - 1)
		{
			std::cout << "Circulating.\n";
			rear = (rear + 1) % theCapacity;
		}

		theSize++;
		objects[rear] = std::move(x);
	}
	Object& dequeue()
	{
		theSize--;
		return objects[++front];
	}

	bool empty() const { return size() == 0; }

	int size() const { return theSize; }
	int capacity() const { return theCapacity; }

	Object& operator[] (int index) const
	{
		return objects[index];
	}

public:

	static const int SPARE_SPACE = 10;
private:

	int front;
	int rear;

	int theCapacity;
	int theSize;

	int* objects;
};
