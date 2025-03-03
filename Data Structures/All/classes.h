#pragma once

#include <iostream>

class Number
{

public:

	Number();

	explicit Number(int value_in);
	explicit Number(int value_in, int sum_in);
	explicit Number(int id_in, int value_in, int sum_in);

	Number(const Number& obj); // Copy Constructor
	//Number(Number&& obj); // Move constructor 

	void operator = (int val);

	//Number operator = (Number&& obj);

	// Getters
	int getValue() const;
	int getSum() const;
	int getID() const;

	// Setters
	void setValue(int val);
	void setSum(int sum_in);

private:
	int id;
	int value;
	int sum;
};