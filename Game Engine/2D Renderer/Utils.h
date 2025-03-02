#pragma once
#include <cmath>

template<class Vector>
float Dist( const Vector p1, const Vector p2 )
{
	return sqrtf( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

template<class Vector>
bool IsInside( const Vector p1, const Vector p2, const Vector size )
{
	return ( ( p1.x >= p2.x && p1.x <= p2.x + size.x && p1.y >= p2.y && p1.y <= p2.y + size.y ) );
}