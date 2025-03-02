#pragma once
#include <cmath>
#include "olcPixelGameEngine.h"

float sq(float x)
{
	return x * x;
}

float DistancePointLine( const olc::vf2d& p0, const olc::vf2d &p1, const olc::vf2d &q ) 
{
	const float a = p0.y - p1.y;
	const float b = p1.x - p0.x;
	const float c = p0.x * p1.y - p1.x * p0.y;

	return std::abs( a * q.x + b * q.y + c) / std::sqrt(sq(a) + sq(b));
}