#pragma once

#include <algorithm>
#include <iostream>

namespace MyList {
	
	template<typename Object>

	class List
	{
	public:

		List() { init(); }
		List(const List& rhs) 
		{
			init();
			for (auto& i : rhs)
				push_back(i);
		}

		List(List&& rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
		{
			rhs.theSize = 0;
			rhs.head = nullptr;
			rhs.tail = nullptr;
		}

		List& operator = ( const List& rhs )
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

		~List()
		{
			clear();
			delete head;
			delete tail;
		}



	private:
		struct Node
		{
			Object data;
			Node* prev;
			Node* next;

			Node(const Object& data = Object{ }, Node* p = nullptr, Node* n = nullptr) : data{ data }, prev{ p }, next{ n } {}
			Node(Object&& data , Node* p = nullptr, Node* n = nullptr) : data{ std::move(data) }, prev{ p }, next{ n } {}

		};

	public:

		class const_iterator 
		{
		public:

			const Object& operator * () const { return retrieve(); }

			const_iterator& operator ++ ()
			{
				current = current->next;
				return *this;
			}
			const_iterator& operator ++ (int)
			{
				const_iterator old = *this;
				++(*this);
				return old;
			}

			const_iterator operator += (int offset)
			{
				const_iterator temp = *this;

				return temp;
			}
			const_iterator operator + (int offset)
			{
				const_iterator temp = *this;

				return temp;
			}

			const_iterator& operator -- ()
			{
				current = current->prev;
				return *this;
			}
			const_iterator& operator -- (int)
			{
				const_iterator old = *this;
				--(*this);
				return old;
			}

			bool operator == (const const_iterator& rhs) const
			{
				return (this->current == rhs.current);
			}

			bool operator != (const const_iterator& rhs) const
			{
				return !(*this == rhs);
			}

		protected:
			
			const List<Object>* theList;

			Node* current;

			Object& retrieve() const { return current->data; }

			const_iterator(const List<Object>& list, Node* p) : theList{ &list }, current { p } {}

			friend class List<Object>;
		};
		class iterator : public const_iterator 
		{
		public:
			Object& operator * () { return const_iterator::retrieve(); }
			const Object& operator * () const { return const_iterator::operator*; }
			
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

			//iterator operator += (int offset)
			//{
			//	iterator temp = *this;

			//	return temp;
			//}
			iterator operator + (int offset)
			{
				iterator temp = *this;

				*temp += offset;

				return temp;
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

			iterator(const List<Object>& list, Node* p) : const_iterator{ list, p } {}

			friend class List<Object>;
		};


	public:

		iterator begin() { return { *this, head->next }; }
		const_iterator begin() const { return { *this, head->next }; }

		iterator end() { return { *this, tail }; }
		const_iterator end() const { return { *this, tail }; }

		Object& front() { return *begin(); }
		Object& back() { return *--end(); }

		const Object& front() const { return *begin(); }
		const Object& back() const { return *--end(); }


		void push_front(const Object& rhs)
		{
			insert(begin(), rhs);
		}
		void push_front(Object&& rhs)
		{
			insert(begin(), std::move(rhs));
		}

		void push_back(const Object& rhs)
		{
			insert(end(), rhs);
		}
		void push_back(Object&& rhs)
		{
			insert(end(), std::move(rhs));
		}

		void pop_front() { erase(begin()); }
		void pop_back() { erase(--end()); }

		int size() const { return theSize; }
		bool empty() const { return size() == 0; }

		void clear()
		{
			while (!empty())
			{
				pop_front();
			}
		}

		iterator erase(iterator itr) 
		{
			Node* p = itr.current;

			iterator nextItr{ *this, p->next };

			p->prev->next = p->next;
			p->next->prev = p->prev;

			delete p;
			theSize--;

			return nextItr;

		}
		iterator erase(iterator from, iterator to)
		{
			for (iterator itr = from; itr != to; )
				itr = erase(itr);

			return to;
		}
		// Insert x before current itr
		iterator insert(iterator itr, const Object& x) 
		{
			Node* p = itr.current;
			//Node* obj{ x, nullptr, nullptr };

			//p->prev->next = obj;
			//obj->prev = p->prev;
			//obj->next = p;
			//p->prev = x;

			theSize++;

			return{ *this, p->prev = p->prev->next = new Node{ x, p->prev, p } };

		}
		// Insert x before current itr
		iterator insert( iterator itr, Object && x ) 
		{
			Node* p = itr.current;

			theSize++;

			return{ *this, p->prev = p->prev->next = new Node{ x, p->prev, p } };
		}

		void swap(iterator itr)
		{
			Node* current = itr.current;
			Node* next = current->next;
			Node* temp = current;

			current->prev->next = next;
			next->prev = current->prev;
			next->next->prev = current;
			current->next = next->next;
			current->prev = next;
			next->next = current;
		}

		iterator operator[] (int index)
		{
			int counter = 0;

			iterator itr = begin();

			while (itr != end())
			{

				if (index == counter)
					return itr;

				counter++;
				itr++;
			}
		}
		const_iterator operator[] (int index) const
		{
			int counter = 0;

			const_iterator itr = begin();

			while (itr != end())
			{

				if (index == counter)
					return itr;

				counter++;
				itr++;
			}
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
}
