#include "Person.h"

Animal::Animal() {}
Animal::Animal(std::string name, int age, char gender) {
	this->name = name;
	this->age = age;
	this->gender = gender;
	this->children = 0;
	this->isDead = false;
}
void Animal::fillInfo(std::string nationality, std::string maritalstatus, std::string job, std::string hobby, int children) {}
//void Animal::fillInfo(int children) {
//	this->children = children;
//
//	std::cout << "Information updated." << std::endl;
//}
void Animal::printInfo() {
	std::cout << "Name: " << name << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Gender: " << gender << std::endl;
}
void Animal::kill() {
	this->isDead = true;
}
void Animal::show() {
	std::cout << "You are an animal." << std::endl;
}
Person::Person() {}
Person::Person(std::string name, int age, char gender) : Animal(name, age, gender) {
	this->breed = "Human";
	this->nationality = " ";
}
void Person::fillInfo(std::string nationality, std::string maritalstatus, std::string job, std::string hobby, int children) {

	if (maritalstatus == "yes")
		this->maritalStatus = "Married";
	else if (maritalstatus == "no")
		this->maritalStatus = "Single";
	else this->maritalStatus = maritalstatus;

	this->nationality = nationality;
	this->occupation = job;
	this->hobby = hobby;
	this->children = children;

	std::cout << "Information updated." << std::endl;
}
void Person::printInfo() {

	std::cout << "Name: " << name << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Gender: " << gender << std::endl;

	if (nationality != " ") {
		std::cout << "Nationality: " << nationality << std::endl;
		std::cout << "Occupation: " << occupation << std::endl;
		std::cout << "Hobby: " << hobby << std::endl;
		std::cout << "Marital Status: " << maritalStatus << std::endl;
		if (children)
			std::cout << "Children: " << children << std::endl;
	}


}
void Person::show() {
	std::cout << "You are a human." << std::endl;
}
Dog::Dog() {}
Dog::Dog(std::string name, std::string owner, int age, char gender) : Animal(name, age, gender) {
	this->breed = "Dog";
	this->owner = owner;
}
void Dog::printInfo() {

	std::cout << "Name: " << name << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Gender: " << gender << std::endl;
	std::cout << "Breed: " << breed << std::endl;
	std::cout << "Owner: " << owner << std::endl;
}
void Dog::show() {
	std::cout << "You are a dog." << std::endl;
}