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

		delete head;
		delete tail;
	}



private:
	struct Node
	{
		CONST TCHAR* data;
		Node* prev;
		Node* next;

		Node(CONST TCHAR* data = NULL, Node* p = nullptr, Node* n = nullptr) : data{ data }, prev{ p }, next{ n } {}

	};

public:

	void push_back(CONST TCHAR* szFile)
	{
		// Insert before end of the list.
		Node* current = tail;

		theSize++;

		current->prev = current->prev->next = new Node{ szFile, current->prev, current };

	}

	CONST TCHAR* front()
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

