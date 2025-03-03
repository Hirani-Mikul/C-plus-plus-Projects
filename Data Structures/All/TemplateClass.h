#pragma once

template<typename Object>

class Value 
{
public:
	explicit Value(const Object& obj = Object{ }) : value{ obj } {}

public:

	void setValue( const Object& value_in )
	{
		value = value_in;
	}

	const Object& getValue() const
	{
		return value;
	}

private:
	Object value;
};
