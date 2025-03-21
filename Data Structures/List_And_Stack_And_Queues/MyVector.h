#pragma once
#include <algorithm>

template<typename Object>

class Vector
{
public:

	explicit Vector(int initSize = 0) : theSize{ 0 }, theCapacity { initSize + SPARE_CAPACITY } 
	{
		objects = new Object[ theCapacity ];
	}

	Vector(const Vector& rhs)
		: theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
	{
		objects = new Object[ theCapacity ];
		for (int k = 0; k < theSize; k++)
			objects[k] = rhs.objects[k];
	}

	Vector& operator = (const Vector& rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector()
	{
		delete[] objects;
	}

	Vector(Vector&& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector& operator = (Vector&& rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

public:

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve( newSize * 2 );

		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		Object* newArray = new Object[ newCapacity ];

		for (int k = 0; k < theSize; k++)
			newArray[k] = std::move(objects[k]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);

		delete[] newArray;
	}

public:
	Object& operator [] (int index)
	{
		if (index >= theSize)
			throw std::exception("Index out of range.\n");

		return objects[index];
	}
	const Object& operator [] (int index) const
	{
		if (index >= theSize)
			throw std::exception("Index out of range.\n");
		return objects[index];
	}

	bool empty() const { return size() == 0; }

	int size() const { return theSize; }

	int capacity() const { return theCapacity; }


	void push_back(const Object& x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);

		objects[theSize++] = x;
	}

	void push_back(Object && x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);

		objects[theSize++] = std::move(x);
	}

	void pop_back()
	{
		--theSize;
	}

	const Object& back() const
	{
		return objects[theSize - 1];
	}

	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}

	iterator end()
	{
		return &objects[size()];
	}
	const_iterator end() const 
	{
		return &objects[size()];
	}

	void insert(int index, const Object& x)
	{
		if (index < 0 || index >= theSize)
			throw std::exception("Insert - Index out of range.\n");

		if (theSize >= theCapacity)
			reserve(2 * theCapacity + 1);

		for (int i = theSize - 1; i >= index; i--)
		{
			objects[i + 1] = std::move(objects[i]);
		}
		objects[index] = x;
		theSize++;
	}
	void insert(int index, Object&& x)
	{
		if (index < 0 || index >= theSize)
			throw std::exception("Insert - Index out of range.\n");

		if (theSize >= theCapacity)
			reserve(2 * theCapacity + 1);

		for (int i = theSize - 1; i >= index; i--)
		{
			objects[i + 1] = std::move(objects[i]);
		}
		objects[index] = std::move(x);
		theSize++;
	}

	void erase(int index)
	{
		if (index < 0 || index >= theSize)
			throw std::exception("Erase - Index out of range!\n");

		for (int i = index; i < theSize - 1; i++)
		{
			objects[i] = objects[i + 1];
		}

		theSize--;
	}

	static const int SPARE_CAPACITY = 5;
private:

	int theSize;
	int theCapacity;

	Object* objects;
};