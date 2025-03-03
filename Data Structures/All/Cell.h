#pragma once
#include <iostream>

class Cell
{
public:
	explicit Cell(int value_in) { value = new int{ value_in }; std::cout << "Cell constructed.\n"; }

	~Cell() { delete value; std::cout << "Cell destructed.\n"; }

	Cell(const Cell& rhs) 
	{
		std::cout << "Cell copied.\n";
		value = new int{ rhs.getValue() };
	}

	Cell(Cell&& rhs) : value{ rhs.value }
	{
		std::cout << "Cell moved.\n";
		rhs.value = nullptr;
	}
	Cell& operator = (const Cell& rhs)
	{
		std::cout << "Cell copied using = operator.\n";
		if (this != &rhs)
			*value = *rhs.value;
		return *this;
	}
	Cell& operator = (Cell&& rhs)
	{
		std::cout << "Cell moved using = operator.\n";
		std::swap(value, rhs.value);
		return *this;
	}

public:

	auto getAdd() const
	{
		return value;
	}

	int getValue() const
	{
		return *value;
	}

	void setValue(int value_in)
	{
		*value = value_in;
	}

private:

	int* value;
};
