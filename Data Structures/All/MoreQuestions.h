#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

template<typename Object>
class Collection
{
public:
	Collection() : arr(0) {}
	Collection(const std::vector<Object> obj) : arr{ obj } {}
	Collection(std::vector<Object>&& obj) : arr{ std::move(obj) } {}

	Collection(int size) : arr(size) {}

public:

	int getSize() const { return arr.size(); }

	bool isEmpty() const { return arr.size() > 0 ? false : true; }
	void makeEmpty()
	{
		arr.clear();
	}
	void insert(const Object& obj)
	{
		arr.push_back(obj);
	}
	void insert(Object&& obj)
	{
		arr.push_back(std::move(obj));
	}
	void remove(const Object obj)
	{
		arr.erase(std::remove_if(arr.begin(), arr.end(), [&](const Object& o) { return o == obj; }), arr.end());

	}

	void print() const
	{
		std::cout << "[ ";
		for (auto& elm : arr)
			std::cout << elm << ", ";
		std::cout << "]";
	}

	bool contains(Object obj)
	{
		auto i = std::find(arr.begin(), arr.end(), obj);

		if (i == arr.end()) return false;

		return true;
	}



private:
	std::vector<Object> arr;
};

template<typename Object>

class OrderedCollection
{
public:
	OrderedCollection() : arr(0) {}
	OrderedCollection(const std::vector<Object>& obj) : arr{ obj } { }
	OrderedCollection(std::vector<Object>&& obj) : arr{ std::move(obj) } {}
	OrderedCollection(int size) : arr(size) {}

public:
	int getSize() const { return arr.size(); }

	bool isEmpty() const { return arr.size() > 0 ? false : true; }
	void makeEmpty()
	{
		arr.clear();
	}
	void insert(const Object& obj)
	{
		arr.push_back(obj);
	}
	void insert(Object&& obj)
	{
		arr.push_back(std::move(obj));
	}
	void remove(const Object obj)
	{
		arr.erase(std::remove_if(arr.begin(), arr.end(), [&](const Object& o) { return o == obj; }), arr.end());

	}

	void print() const
	{
		std::cout << "[ ";
		for (auto& elm : arr)
			std::cout << elm << ", ";
		std::cout << "]";
	}

	bool contains(Object obj)
	{
		auto i = std::find(arr.begin(), arr.end(), obj);

		if (i == arr.end()) return false;

		return true;
	}


	Object& findMin()
	{
		int maxIndex = 0;

		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[maxIndex] > arr[i])
				maxIndex = i;
		}

		return arr[maxIndex];
	}
	Object& findMax()
	{
		int maxIndex = 0;

		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[maxIndex] < arr[i])
				maxIndex = i;
		}

		return arr[maxIndex];
	}

	int search(const Object& target) const {

		int start = 0;
		int end = arr.size() - 1;

		return binarySearch(start, end, target);

	}

	Object& operator[](int index) 
	{
		return arr[index];
	}

private:

	int binarySearch(int start, int end, const Object& target) const
	{
		if (start > end) return -1;

		int midIndex = std::floor((start + end) / 2);

		if (arr[midIndex] == target) return midIndex;

		if (arr[midIndex] > target) return binarySearch(start, midIndex - 1, target);
		else return binarySearch(midIndex + 1, end, target);
	}

private:
	std::vector<Object> arr;
};


/*
	TESTING PURPOSE
*/

class Person
{
public:
	Person(int _id, int _age, const char* _name, char _gender, float _height) : id{ _id }, age{ _age }, name{ _name }, gender{ _gender }, height{ _height } { std::cout << _id << " created.\n"; }

public:

	int getID() const { return id; }
	int getAge() const { return age; }
	void setAge(int _age) { age = _age; }

	std::string getName() { return name; }

	friend std::ostream& operator << (std::ostream& out, const Person& p);

	bool operator < ( const Person& p ) const
	{
		std::string lhs = name;
		std::string rhs = p.name;

		std::for_each(lhs.begin(), lhs.end(), [](char& c) { c = ::tolower(c); });
		std::for_each(rhs.begin(), rhs.end(), [](char& c) { c = ::tolower(c); });

		if ((int)lhs[0] < (int)rhs[0]) return true;
		else return false;

	}
	bool operator > (const Person& p) const
	{
		std::string lhs = name;
		std::string rhs = p.name;

		std::for_each(lhs.begin(), lhs.end(), [](char& c) { c = ::tolower(c); });
		std::for_each(rhs.begin(), rhs.end(), [](char& c) { c = ::tolower(c); });

		if ((int)lhs[0] > (int)rhs[0]) return true;
		else return false;
	}

	bool operator == (const Person& p) const
	{
		std::string lhs = name;
		std::string rhs = p.name;

		std::for_each(lhs.begin(), lhs.end(), [](char& c) { c = ::tolower(c); });
		std::for_each(rhs.begin(), rhs.end(), [](char& c) { c = ::tolower(c); });

		if (lhs == rhs) return true;
		else return false;
	}

private:
	int id;
	int age;
	std::string name;
	char gender;
	float height;
};

std::ostream& operator << (std::ostream& out, const Person& p)
{
	out << "{ ";
	out << "_id: " << p.id << ", ";
	out << "Name: " << p.name << ", ";
	out << "Age: " << p.age << ", ";
	out << "Gender: " << p.gender << ", ";
	out << "}\n";

	return out;
}