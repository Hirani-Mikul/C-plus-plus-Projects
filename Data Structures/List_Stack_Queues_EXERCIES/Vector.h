#pragma once
#include <algorithm>
#include <exception>
#include <iostream>

class IteratorOutOfBoundsException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Exception :- Iterator out of bound!\n";
	}
};

//typedef int Object;
template<typename Object>

class Vector
{
public:

	class const_iterator;
	class iterator;
	// Big 5

	Vector() : theSize{ 0 }, theCapacity{ SPARE_CAPACITY }, objects{ new Object[theCapacity] }   {  }
	Vector(size_t initialCapacity) : theSize{ 0 }, theCapacity{ initialCapacity }, objects{ new Object[theCapacity] } {}

	Vector(const Vector& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr } 
	{
		objects = new Object[theCapacity];

		for (int i = 0; i < theSize; i++)
			objects[i] = rhs.objects[i];
	}
	Vector(Vector&& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects } 
	{
		rhs.objects = nullptr;
		rhs.theCapacity = 0;
		rhs.theSize = 0;
	}

	Vector& operator = (const Vector& rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);

		return *this;
	}
	Vector& operator = ( Vector&& rhs)
	{
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(theSize, rhs.theSize);
		std::swap(objects, rhs.objects);

		return *this;
	}

	// Using intializer list


	Vector(const std::initializer_list<Object>& list) : theSize{ 0 }, theCapacity{ list.size() + SPARE_CAPACITY }, objects{ nullptr } 
	{
		objects = new Object[theCapacity];

		//for (auto& elm : list)
		//{
		//	push_back(elm);
		//}


		for (auto& elm : list)
		{
			push_back(std::move(elm));
		}
	
	}

	~Vector()
	{
		clear();
		::operator delete(objects, theCapacity * sizeof(Object));

	}
	
public:
	// Operator overloaders

	const Object& operator[] (int index) const 
	{
		if (index < 0 || index > theSize)
			throw std::exception("Index out of bound range!");

		return objects[index]; 
	}
	Object& operator[] (int index) 
	{ 
		if (index < 0 || index > theSize)
			throw std::exception("Index out of bound range!");

		return objects[index];
	}

public:
	void resize(size_t newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize);

		theSize = newSize;
	}
	void reserve(size_t newCapacity)
	{
		Object* newArr = (Object*)::operator new(newCapacity * sizeof(Object));

		if (newCapacity < theSize)
			theSize = newCapacity;

		for (int i = 0; i < theSize; i++)
		{
			new(&newArr[i]) Object(std::move(objects[i]));
			//newArr[i] = std::move(objects[i]);
		}

		for (int i = 0; i < theSize; i++)
			objects[i].~Object();

		::operator delete(objects, theCapacity * sizeof(Object));

		objects = newArr;
		theCapacity = newCapacity;
	}

public:
	// Setters & others
	template<typename... Args>
	Object& emplace_back(Args&... args)
	{
		if (theSize >= theCapacity)
			reserve(theCapacity + theCapacity / 2);

		new(&objects[theSize]) Object(std::forward<Args>(args)...);

		return objects[theSize++];
	}
	
	void push_back( const Object& x )
	{
		if (theSize >= theCapacity)
			reserve(theCapacity + theCapacity / 2);

		objects[theSize++] = x;
	}
	void push_back( Object && x)
	{
		if (theSize >= theCapacity)
			reserve(theCapacity + theCapacity / 2);

		objects[theSize++] = std::move(x);
	}

	void pop_back()
	{
		// Throw exception if theSize <= 0
		if (theSize <= 0) return;

		objects[theSize--].~Object();
	}

	void clear()
	{
		for (int i = 0; i < theSize; i++)
			objects[i].~Object();

		theSize = 0;
	}
	// Insert before itr
	iterator insert(iterator itr, const Object& val)
	{
		// Re-allocating will make itr stale
		if (theSize >= theCapacity)
			reserve(theCapacity + theCapacity / 2);

		for (iterator i = end() - 1; i >= itr; i--)
		{
			auto next = i;
			next++;
			*next = std::move(*i);
		}

		*itr = val;
		theSize++;

		return itr;

	}
	iterator insert(iterator itr, Object && val)
	{
		// Re-allocating will make itr stale

		if (theSize >= theCapacity)
			reserve(theCapacity + theCapacity / 2);

		for (iterator i = end() - 1; i >= itr; i--)
		{
			*(i + 1) = std::move(*i);
			//auto next = i;
			//next++;
			//*next = std::move(*i);
		}

		*itr = std::move(val);
		theSize++;

		return itr;
	}
	iterator erase(iterator itr)
	{
		for (auto i = itr; i < end(); i++)
		{
			*i = std::move(*(i + 1));

			/*auto next = i;
			next++;
			*i = std::move(*next);*/
		}

		theSize--;

		return itr;
	}

public:
		// Getters & others

		const_iterator begin() const { return { *this, &objects[0] }; }
		const_iterator end() const { return { *this, &objects[theSize] }; }

		iterator begin() { return { *this, &objects[0] }; }
		iterator end() { return { *this, &objects[theSize] }; }

		Object& back() { return objects[theSize - 1]; }
		const Object& back() const { return objects[theSize - 1]; }

		bool empty() const { return theSize == 0; }
		size_t size() const { return theSize; }
		size_t capacity() const { return theCapacity; }

public:

	class const_iterator 
	{
	public:

		const_iterator() : current{ nullptr } {}

		const Object& operator * () const 
		{ 
			return retrieve(); 
		}

		const_iterator& operator ++ () 
		{ 
			current++;
			return *this;
		}
		const_iterator operator ++ (int)
		{
			const_iterator old = *this;
			++(*this);

			return old;
		}

		const_iterator operator -- ()
		{
			current--;
			return *this;
		}

		const_iterator operator -- (int)
		{
			const_iterator old = *this;
			--(*this);
			return old;
		}

		const_iterator operator += ( int offset )
		{
			//current += sizeof(Object) * offset;
			current += offset;
			return *this;
		}
		const_iterator operator -= (int offset)
		{
			//current -= sizeof(Object) * offset;
			current -= offset;
			return *this;
		}

		const_iterator operator + (int offset) const
		{
			const_iterator next = *this;
			next += offset;
			return next;
		}
		const_iterator operator - (int offset) const
		{
			const_iterator next = *this;
			next -= offset;
			return next;
		}

		//const_iterator operator + (int offset)
		//{
		//	current += offset;
		//	return *this;
		//}
		//const_iterator operator - (int offset)
		//{
		//	current -= offset;
		//	return *this;
		//}

		bool operator < (const const_iterator& rhs) const
		{
			return current < rhs.current;
		}
		bool operator > (const const_iterator& rhs) const
		{
			return current > rhs.current;
		}
		bool operator <= (const const_iterator& rhs) const
		{
			return !(rhs.current < current);
		}
		bool operator >= (const const_iterator& rhs) const
		{
			return !(current < rhs.current);
		}

		bool operator == (const const_iterator& rhs) const { return current == rhs.current; }

		bool operator != (const const_iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		Object* current;

		const Vector<Object>* theVec;
		//const Vector* theVec;

		void assertIsValid() const
		{
			if (!((theVec->begin() <= *this) && (*this <= theVec->end())))
			{
				std::cout << "The vec: " << &(*theVec->begin()) << '\n';
				throw std::exception("Iterator out of bound.");
			}
		}

		Object& retrieve() const 
		{
			assertIsValid();
			return *current; 
		}

		const_iterator(const Vector<Object>& vec, Object* obj) : theVec{ &vec }, current { obj } {}
		//const_iterator(const Vector& vec, Object* obj) : theVec{ &vec }, current { obj } {}

		friend class Vector<Object>;
		//friend Vector;
	};

	class iterator : public const_iterator
	{
	public:
		iterator() {}

		Object& operator * () { return const_iterator::retrieve(); }

		const Object& operator * () const { return const_iterator::operator*(); }

		iterator& operator ++ ()
		{
			
			this->current++;
			return *this;
		}
		iterator operator ++ (int)
		{
			iterator old = *this;
			++(*this);

			return old;
		}

		iterator operator -- ()
		{
			this->current--;
			return *this;
		}

		iterator operator -- (int)
		{
			iterator old = *this;
			--(*this);
			return old;
		}

		iterator operator += (int offset)
		{
			//current += sizeof(Object) * offset;
			this->current += offset;
			return *this;
		}
		iterator operator -= (int offset)
		{
			//current -= sizeof(Object) * offset;
			this->current -= offset;
			
			return *this;
		}

		iterator operator + (int offset) const
		{
			iterator next = *this;
			next += offset;
			return next;
		}
		iterator operator - (int offset) const
		{
			iterator next = *this;
			next -= offset;
			return next;
		}

		bool operator == (const iterator& rhs) const { return this->current == rhs.current; }

		bool operator != (const iterator& rhs) const
		{
			return !(*this == rhs);
		}

		bool operator < (const iterator& rhs) const
		{
			return this->current < rhs.current;
		}
		bool operator > (const iterator& rhs) const
		{
			return this->current > rhs.current;
		}
		bool operator <= (const iterator& rhs) const
		{
			return !(rhs.current < this->current);
		}
		bool operator >= (const iterator& rhs) const
		{
			return !(this->current < rhs.current);
		}


	protected:

		//iterator(const Vector& vec, Object* obj) : const_iterator{ vec, obj } {}
		iterator(const Vector<Object>& vec, Object* obj) : const_iterator{ vec, obj } {}
		//friend Vector;
		friend class Vector<Object>;
	};



public:
	static const int SPARE_CAPACITY = 5;


private:

	size_t theSize;
	size_t theCapacity;

	Object* objects;
};