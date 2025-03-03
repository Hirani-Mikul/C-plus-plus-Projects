#include "classes.h"

Number::Number()
{
	std::cout << "Constructor called: 0 Parameters.\n";
}
Number::Number(int value_in = 10) : value(value_in)
{
	sum = 0;
	std::cout << "Consturctor called: 1 Parameter.\n";
}

Number::Number(int value_in, int sum_in) : value{ value_in }, sum{ sum_in }
{
	std::cout << "Constructor called: 2 Parameters.\n";
}

Number::Number(int id_in, int value_in, int sum_in) : id{ id_in }, value{ value_in }, sum{ sum_in }
{
	std::cout << "Constructor called: 3 Parameters.\n";
}
//Number::Number(Number && obj)
//{
//	std::cout << "Object Moved.\n";
//}
Number::Number(const Number& obj)
{
	std::cout << "Object copied.\n";

	id = obj.id;
	value = obj.value;
	sum = obj.sum;
	//value = obj.sum;
	//sum = obj.value;
}

void Number::operator=(int val)
{
	value = sum;
	sum = val;
	std::cout << "Values changed.\n";
}
//Number Number::operator=(Number && obj)
//{
//	std::cout << "Move assignment.\n";
//}

int Number::getValue() const { return value; }
int Number::getSum() const { return sum; }
int Number::getID() const { return id; }

void Number::setValue(int val) { value = val; }
void Number::setSum(int sum_in) { sum = sum_in; }
