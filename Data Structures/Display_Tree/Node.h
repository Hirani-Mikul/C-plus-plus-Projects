#pragma once

#include "Entity.h"

class Node : public Entity
{
public:

	Node(olc::vf2d pos, olc::Pixel col, float scale, float radius, char elm) : Entity{ pos, col, scale }, m_Radius{ radius }, m_Element{ elm } {}

public:
private:

	float m_Radius;

	char m_Element;
};