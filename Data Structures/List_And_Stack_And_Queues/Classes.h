#pragma once
#include <string>
#include <iostream>

class Person
{
public:
	explicit Person()
	{
		id = 0;
		name = "Unknown";
		age = 1;
		gender = 'U';
	}

	Person( int _id, const char* _name, int _age, char _gender ) : id(_id), name(_name), age(_age), gender(_gender) {}

	bool operator== ( const Person& rhs )
	{
		return id == rhs.id;
	}

public:

	int getId() const { return id; }
	int getAge() const { return age; }
	char getGender() const { return gender; }

	std::string getName() const { return name; }

	void setName(std::string _name) { name = _name; }

private:
	int id;
	
	std::string name;
	int age;
	char gender;
};
