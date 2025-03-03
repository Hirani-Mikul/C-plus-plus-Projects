#pragma once
#include <Windows.h>
#include <iostream>
#include <array>


/*
	Thread one will read and remove elements from list
	while thread two only writes to the thread.

	Thread one will read and remove from head
	Thread two will insert at the tail



	The elements are file names.
	The maximum file's name length is 256 bytes.

	
*/

/*
	THE LIST DESIGN

	The list will be a QUEUE.

	The maximum number of elements that can be stored inside a queue is 15.
	Once the limit is approaced, the thread two must wait for the queue to be processed by thread one.

*/



class Queue {

public:
	Queue() : mSize{ 0 }, mCapacity{ 15 }, mObjects{ nullptr }, mFront{ -1 }, mRear{ -1 } {
		
		mObjects = new TCHAR*[15];

		for (int i = 0; i < 15; i++)
			mObjects[i] = new TCHAR[256];
	}

	~Queue()
	{
		for (int i = 0; i < 15; i++)
		{
			delete[] mObjects[i];
		}

		delete[] mObjects;
	}


public:
	void enqueue(TCHAR*& elm)
	{
		// Check if the queue is full

		mSize++;
		mObjects[++mRear] = elm;
	}

	void enqueue(TCHAR*&& elm)
	{
		mRear++;

		if (mSize == mCapacity)
			return; // The thread should wait

		if (mRear == mCapacity - 1)
			mRear = (mRear + 1) % mCapacity;

		mSize++;
		mObjects[mRear] = std::move(elm);
	}

	TCHAR*& dequeue()
	{
		mSize--;
		return mObjects[++mFront];
	}

	bool empty() const { return size() == 0; }

	short int size() const { return mSize; }
	short int capacity() const { return mCapacity; }

private:
	short int mFront;
	short int mRear;
	short int mCapacity;
	short int mSize;

	TCHAR** mObjects;
};