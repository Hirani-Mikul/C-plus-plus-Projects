#pragma once
#include <iostream>

class Square
{
public:
	explicit Square( double s = 0.0 ) : side{ s } {}


public:

	double getSide() const { return side; }
	double getArea() const { return ( side * side ); };
	double getPerimeter() const { return (side * 4); }

	void print( std::ostream& out ) const
	{
		out << "square " << getSide() << '\n';
	}

	bool operator<( const Square& rhs ) const
	{
		return getSide() < rhs.getSide();
	}

private:
	double side;
};
