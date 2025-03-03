#pragma once
#include <iostream>
#include <algorithm>

template<typename Object>

class List
{
private:
	struct Node
	{
		Object data;
		Node* prev;
		Node* next;

		Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr) : data{ d }, prev{ p }, next{ n } {}

		Node(Object&& d, Node* p = nullptr, Node* n = nullptr) : data{ std::move(d) }, prev{ p }, next{ n } {}
	};

public:

	class const_iterator
	{
	public:
		const_iterator() : current{ nullptr } {}

		const Object& operator * () const { return retrieve(); }

		const_iterator& operator ++ ()
		{
			current = current->next;
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
			current = current->prev;
			return *this;
		}

		const_iterator operator -- (int)
		{
			const_iterator old = *this;
			--(*this);
			return old;
		}

		bool operator == (const const_iterator& rhs) const { return current == rhs.current; }

		bool operator != (const const_iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:

		const List<Object>* theList;

		Node* current;

		void assertIsValid() const
		{
			if (theList == nullptr || current == nullptr || current == theList->head)
			{
				std::cout << "Iterator out of bound.\n";
				throw std::exception("Iterator ouf of bound.");
			}
			//throw IteratorOutOfBoundsException{};
		}

		Object& retrieve() const
		{
			assertIsValid();
			return current->data;
		}

		const_iterator(const List<Object>& lst, Node* p) : theList{ &lst }, current{ p } {}

		friend class List<Object>;

	};
	class iterator : public const_iterator
	{
	public:
		iterator() {}

		Object& operator * ()
		{
			return const_iterator::retrieve();
		}

		const Object& operator* () const
		{
			return const_iterator::operator*();
		}

		iterator& operator ++ ()
		{
			this->current = this->current->next;
			return *this;
		}
		iterator& operator ++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		iterator& operator -- ()
		{
			this->current = this->current->prev;
			return *this;
		}
		iterator& operator -- (int)
		{
			iterator old = *this;
			--(*this);
			return old;
		}

	protected:
		iterator(const List<Object>& lst, Node* p) : const_iterator{ lst, p } {}

		friend class List<Object>;
	};


public:
	
	class const_reverse_iterator : public const_iterator
	{
	public:
		const_reverse_iterator() {}

		const Object& operator * () const { return const_iterator::retrieve(); }

		const_reverse_iterator& operator ++ ()
		{
			this->current = this->current->prev;
			return *this;
		}
		const_reverse_iterator operator ++ (int)
		{
			const_reverse_iterator old = *this;
			++(*this);
			return old;
		}
		const_reverse_iterator operator -- ()
		{
			this->current = this->current->next;
			return *this;
		}

		const_reverse_iterator operator -- (int)
		{
			const_reverse_iterator old = *this;
			--(*this);
			return old;
		}

		bool operator == (const const_reverse_iterator& rhs) const { return this->current == rhs.current; }

		bool operator != (const const_reverse_iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:

		const_reverse_iterator(const List<Object>& lst, Node* p) : const_iterator{ lst, p } {}

		friend class List<Object>;
	};

	class reverse_iterator : public const_reverse_iterator
	{
	public:
		reverse_iterator() {}

		const Object& operator * () const { return const_reverse_iterator::operator*(); }

		Object& operator * ()
		{
			return const_reverse_iterator::retrieve();
		}

		reverse_iterator& operator ++ ()
		{
			this->current = this->current->prev;
			return *this;
		}
		reverse_iterator operator ++ (int)
		{
			reverse_iterator old = *this;
			++(*this);
			return old;
		}
		reverse_iterator operator -- ()
		{
			this->current = this->current->next;
			return *this;
		}

		reverse_iterator operator -- (int)
		{
			reverse_iterator old = *this;
			--(*this);
			return old;
		}

		bool operator == (const reverse_iterator& rhs) const { return this->current == rhs.current; }

		bool operator != (const reverse_iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:

		reverse_iterator(const List<Object>& lst, Node* p) : const_reverse_iterator{ lst, p } {}

		friend class List<Object>;
	};




public:
	List() { init(); }
	List(const List& rhs)
	{
		init();
		for (auto& x : rhs)
			push_back(x);
	}
	~List()
	{
		clear();
		delete head;
		delete tail;
	}

	List(List&& rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
	{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}

	List& operator = (const List& rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	List& operator = (List&& rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);

		return *this;
	}

	Object& operator[] (int index)
	{
		int counter = 0;

		iterator itr = begin();

		while (itr != end())
		{

			if (index == counter)
				return *itr;

			counter++;
			itr++;
		}
	}
	const Object& operator[] (int index) const
	{
		int counter = 0;

		const_iterator itr = begin();

		while (itr != end())
		{

			if (index == counter)
				return *itr;

			counter++;
			itr++;
		}
	}

public:
	iterator begin() { return { *this, head->next }; }
	const_iterator begin() const
	{
		const_iterator itr{ *this, head };
		return ++itr;
	}

	reverse_iterator rbegin() { return { *this, tail->prev }; }
	
	const_reverse_iterator rbegin() const { return { *this, tail->prev }; }

	iterator end() { return { *this, tail }; }
	const_iterator end() const { return { *this, tail }; }
	
	reverse_iterator rend() { return { *this, head }; }
	
	const_reverse_iterator rend() const { return { *this, head }; }

	int size() const { return theSize; }
	bool empty() const { return size() == 0; }

	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}

	Object& front() { return *begin(); }
	const Object& front() const { return *begin(); }

	Object& back() { return *--end(); }
	const Object& back() const { return *--end(); }

	void push_front(const Object& x)
	{
		insert(begin(), x);
	}
	void push_front(Object&& x)
	{
		insert(begin(), std::move(x));
	}

	void push_back(const Object& x)
	{
		insert(end(), x);
	}
	void push_back(Object&& x)
	{
		insert(end(), std::move(x));
	}

	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}

	iterator insert(iterator itr, const Object& x)
	{
		itr.assertIsValid();

		if (itr.theList != this)
			std::cout << "Iterator mismatch.\n";
		//throw IteratorMismatchException{};

		Node* p = itr.current;
		theSize++;

		return { *this, p->prev = p->prev->next = new Node{ x, p->prev, p } };
		//return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
	}
	iterator insert(iterator itr, Object&& x)
	{
		Node* p = itr.current;
		theSize++;

		return { *this, p->prev = p->prev->next = new Node{ x, p->prev, p } };
		//return { *this, p->prev = p->prev->next  };
		//return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } };
	}

	iterator erase(iterator itr)
	{
		Node* p = itr.current;
		iterator retVal{ *this, p->next };
		p->prev->next = p->next;
		p->next->prev = p->prev;

		delete p;
		theSize--;

		return retVal;
	}
	iterator erase(iterator from, iterator to)
	{
		for (iterator itr = from; itr != to; )
			itr = erase(itr);

		return to;
	}

	void splice(iterator position, List<Object>& lst)
	{
		//removes all the items from lst, placing them prior to position in List* this.lst
		//	and* this must be different lists.Your routine must run in constant time.
		iterator _where = position;
		for (iterator itr = lst.begin(); itr != lst.end(); itr++)
		{
			_where = insert(_where, std::move(*itr));
			//_where = insert(_where, std::move(lst.front()));
			//lst.pop_front();
		}

		lst.clear();
	}

private:

	int theSize;

	Node* head;
	Node* tail;

	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};