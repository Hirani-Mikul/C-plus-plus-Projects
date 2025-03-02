#pragma once
#include "olcPixelGameEngine.h"

constexpr double PI_D = 3.14159265358979323846;
constexpr float PI = (float)PI_D;

auto Dist( olc::vf2d p1, olc::vf2d p2 ) 
{
	return sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

auto Dist( olc::vf2d p1, olc::vf2d p2, float r ) {

	return fabs((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) < r * r;
}

auto Dist( olc::vf2d p1, olc::vf2d p2, float r, float r2 ) {

	return fabs((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)) <= (r + r2) * (r + r2);
}

olc::vf2d GetRotated( olc::vf2d p, float angle )
{
	const float cosTheta = cosf(angle);
	const float sinTheta = sinf(angle);

	const float newx = p.x * cosTheta - p.y * sinTheta;
	p.y = p.x * sinTheta + p.y * cosTheta;
	p.x = newx;

	return p;
}


// USE OF SINGLETON

class Random {
public:
	Random(const Random&) = delete;

	static Random& Get()
	{
		return s_Instance;
	}

	float GetRand_F( const int min = 0, const int max = 1 )
	{
		return (float)( rand() % max + (min));
	}
	int GetRand_N( const int min = 0, const int max = 1 )
	{
		return (rand() % max + (min));
	}

	float GetRand_F2(const int min = 0, const int max = 1)
	{
		return (float)(rand() % (max * 2) + (min));
	}
	int GetRand_N2(const int min = 0, const int max = 1)
	{
		return (rand() % (max * 2) + (min));
	}

private:
	Random() {}

	static Random s_Instance;
};

Random Random::s_Instance;
