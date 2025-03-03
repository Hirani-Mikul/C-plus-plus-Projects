#pragma once
#include "Entity.h"
#include <algorithm>

class cCircle : public Entity
{
public:
	cCircle( olc::vf2d pos, int verts, float radius, olc::Pixel col );
	
public:
	float GetRadius() const;
	
	
private:
	float m_Radius;

};

class Node : public Entity
{
public:
	Node(olc::vf2d pos, int verts, float radius, olc::Pixel col) : Entity(Circle::Make(verts), pos, radius, col), m_Radius(radius)
	{
	}

private:
	float m_Radius;
};