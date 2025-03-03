#include <iostream>
#include <vector>
#include "Vector.h"
#include "List.h"
#include "Stack.h"

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';



int Stack_Testing()
{
	Stack<int> nums;

	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);

	std::cout << "Size: " << nums.size() << '\n';
	std::cout << "Capacity: " << nums.capacity() << '\n';

	std::cout << "Top: " << nums.top() << '\n';


	_New(2);
	_Wait();
	return 0;
}

int EX_3_16()
{
	List<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(5);

	std::cout << "Size: " << nums.size() << '\n';

	auto itr = nums.begin();
	itr++;

	auto itr2 = nums.begin();
	itr2++;

	nums.erase(itr);

	std::cout << "Element: " << *itr << "\n";

	for (auto i = nums.begin(); i != nums.end(); i++)
		std::cout << *i << ", ";

	_New(2);

	for (auto i = nums.rbegin(); i != nums.rend(); i++)
		std::cout << *i << ", ";


	_New(2);
	_Wait();
	return 0;
}

void printList(const List<int>&lst)
{
	for (auto& elm : lst)
		std::cout << elm << ", ";
}

int EX_3_15()
{
	List<int> list;
	List<int> list2;

	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);

	list2.push_back(7);
	list2.push_back(8);
	list2.push_back(9);
	list2.push_back(10);
	list2.push_back(11);
	list2.push_back(12);

	std::cout << "Size of List 1: " << list.size() << '\n';

	_New(2);

	std::cout << "List 1:\t\t";
	printList(list);


	List<int>::iterator itr = list.begin();
	itr++;

	list.splice(itr, list2);

	_New(2);
	std::cout << "List 2:\t\t";
	printList(list2);

	_New(2);

	std::cout << "After splicing...\n";
	std::cout << "List 1:\t\t";
	printList(list);

	_New(2);
	std::cout << "Size of List 1: " << list.size() << '\n';
	std::cout << "Size of List 2: " << list2.size() << '\n';

	_New(2);
	_Wait();
	return 0;
}

int EX_3_1_0_V2()
{
	Vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


	nums.push_back(11);
	nums.push_back(12);

	nums.push_back(13);
	nums.push_back(14);
	nums.push_back(15);

	std::cout << "Size: " << nums.size() << '\n';
	std::cout << "Capacity: " << nums.capacity() << '\n';


	_New(2);

	for (auto i = nums.begin(); i != nums.end(); i++)
		std::cout << *i << ", ";

	_New(2);
	_Wait();
	return 0;
}

int EX_3_1_0_()
{
	Vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::vector<int> vals = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::cout << "Size: " << nums.size() << '\n';
	std::cout << "Capacity: " << nums.capacity() << '\n';

	_New(2);
	nums.push_back(100);
	nums.push_back(101);
	//nums.push_back(102);
	//nums.push_back(103);

	//Vector::iterator itr = nums.begin() + 2;
	//nums.push_back(105); // This push_back call will make the itr stale (invalid)
	//std::cout << "Element: " << *itr << '\n';
	Vector<int>::iterator itr = nums.begin() + 6;

	int val = 32;
	nums.insert(itr, val);
	nums.insert(itr, val + 10);
	nums.insert(itr, val + 20);

	itr = nums.erase(itr + 1);

	_New(2);

	for (int i = 0; i < nums.size(); i++)
		std::cout << nums[i] << ", ";

	_New(2);

	std::cout << "Size: " << nums.size() << '\n';
	std::cout << "Capacity: " << nums.capacity() << '\n';

	_New(2);

	_Wait();
	return 0;
}