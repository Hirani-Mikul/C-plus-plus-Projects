#pragma once

#include <algorithm>
#include <Windows.h>

class MyQueue
{
public:

	MyQueue() { init(); }

	~MyQueue()
	{
		clear();

		delete[] head->data;
		delete[] tail->data;

		delete head;
		delete tail;
	}



private:
	struct Node
	{
		TCHAR* data;
		Node* prev;
		Node* next;

		Node(TCHAR* data = new TCHAR[1], Node* p = nullptr, Node* n = nullptr) : data{ data }, prev{ p }, next{ n } {}

	};

public:

	void push_back(TCHAR* szFile)
	{
		// Insert before end of the list.
		Node* current = tail;

		theSize++;

		current->prev = current->prev->next = new Node{ szFile, current->prev, current };

	}

	const TCHAR* front()
	{
		return head->next->data;
	}

	void pop_front()
	{
		// Removes the first file in the list.
		Node* current = head->next;

		current->prev->next = current->next;
		current->next->prev = current->prev;

		delete[] current->data;
		delete current;

		theSize--;

	}

	int size() const { return theSize; }
	bool empty() const { return size() == 0; }

	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}

	void print()
	{
		Node* current = head->next;

		while (current->next)
		{
			std::wcout << "Name: " << current->data << "\n";

			current = current->next;
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

