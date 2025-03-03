#pragma once

#include <algorithm>

template<typename Object>

class L_Stack
{
private:

	struct Node
	{
		Object data;
		Node* prev;
		Node* next;

		Node(const Object& rhs = Object{}, Node* p = nullptr, Node* n = nullptr) : data{ rhs }, prev{ p }, next{ n } {}
		Node(Object&& rhs, Node* p = nullptr, Node* n = nullptr) : data{ std::move(rhs) }, prev{ p }, next{ n } {}
	};

public:

	class const_iterator 
	{
	public:

		const_iterator() : current{ nullptr } {}
		
		const Object& operator * () { return retrieve(); }

		const_iterator& operator++ () 
		{
			current = current->next;

			return *this;
		}
		const_iterator operator++ (int) 
		{
			const_iterator old = *this;

			++(*this);

			return old;
		}

		const_iterator& operator-- ()
		{
			current = current->prev;

			return *this;
		}
		const_iterator operator-- (int)
		{
			const_iterator old = *this;

			--(*this);

			return old;
		}

		bool operator == (const const_iterator& rhs) const { return current == rhs.current; }
		bool operator != (const const_iterator& rhs) const { return !(*this == rhs); }
		
	protected:

		Node* current;

		Object& retrieve() const { return current->data; }

		const_iterator(Node* c) : current{ c } {}

		//friend L_Stack<Object>;
	};
	class iterator : public const_iterator 
	{
	public:
		iterator() : const_iterator{ nullptr } {}

		Object& operator * () { return const_iterator::retrieve(); }
		const Object& operator * () const { return const_iterator::operator*(); }

		iterator& operator++ ()
		{
			this->current = this->current->next;

			return *this;
		}
		iterator operator ++ (int)
		{
			iterator old = *this;
			++(*this);

			return old;
		}

		iterator& operator-- ()
		{
			this->current = this->current->prev;

			return *this;
		}
		iterator operator -- (int)
		{
			iterator old = *this;
			--(*this);

			return old;
		}


	protected:

		iterator(Node* c) : const_iterator{ c } {}

		friend L_Stack<Object>;

	};

public:

	iterator begin() { return { head->next }; }
	const_iterator begin() const { return { head->next }; }

	iterator end() { return { tail }; }
	const_iterator end() const { return { tail }; }

	int size() const { return topOfStack + 1; }
	bool empty() const { return size() == 0; }
	void clear() 
	{
		while (topOfStack != -1)
		{
			pop();
		}
	}

	void push_back(const Object& x) 
	{
		insert(end(), x);
	}
	void push_back(Object && x ) 
	{
		insert(end(), std::move(x));
	}

	iterator insert( iterator itr, const Object& x )
	{
		Node* p = itr.current;
		topOfStack++;

		return { p->prev = p->prev->next = new Node{ x, p->prev, p } };

	}

	iterator insert(iterator itr, Object&& x)
	{
		Node* p = itr.current;
		topOfStack++;

		return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
	}

	iterator erase(iterator itr)
	{
		Node* p = itr.current;

		iterator retVal{ p->next };

		p->prev->next = p->next;
		p->next->prev = p->prev;

		delete p;
		topOfStack--;

		return retVal;
	}

	Object& top() 
	{
		return *--end();
	}
	const Object& top() const { return *begin(); }

	void pop()
	{
		erase(--end());
	}

public:

	L_Stack() { init(); }

	L_Stack(const L_Stack& rhs)
	{
		init();

		for (auto& x : rhs)
			push_back(x);

	}
	L_Stack(L_Stack&& rhs) : topOfStack{ rhs.topOfStack }, head{ rhs.head }, tail{ rhs.tail } 
	{
		rhs.topOfStack = -1;
		rhs.head = nullptr;
		rhs.tail = nullptr;
	}

	L_Stack& operator = (const L_Stack& rhs)
	{
		L_Stack copy = rhs;
		std::swap(*this, copy);

		return *this;
	}
	L_Stack& operator = (L_Stack&& rhs)
	{
		std::swap(topOfStack = rhs.topOfStack);
		std::swap(head = rhs.head);
		std::swap(tail = rhs.tail);

		return *this;
	}

	~L_Stack()
	{
		clear();
		delete head;
		delete tail;
	}

private:

	int topOfStack;

	Node* head;
	Node* tail;

	void init()
	{
		topOfStack = -1;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};