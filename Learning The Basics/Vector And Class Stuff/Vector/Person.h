#pragma once
#include <iostream>
class Animal
{
protected:
	std::string name;
	int age;
	char gender;
	int children;
	std::string breed;

public:
	bool isDead;
	Animal();
	Animal(std::string name, int age, char gender);
	virtual void fillInfo(std::string nationality, std::string maritalStatus, std::string occupation, std::string hobby, int children);
	virtual void printInfo();
	virtual void show();
	virtual void kill();
};

class Person : public Animal {
private:
	std::string nationality;
	std::string maritalStatus;
	std::string occupation;
	std::string hobby;

public:
	Person();
	Person(std::string name, int age, char gender);
	void fillInfo(std::string nationality, std::string maritalstatus, std::string occupation, std::string hobby, int children);
	void printInfo();
	void show();

};

class Dog : public Animal {
private: 
	std::string owner;

public:

	Dog();
	Dog(std::string name, std::string owner, int age, char gender);
	void printInfo();
	void show();
};
