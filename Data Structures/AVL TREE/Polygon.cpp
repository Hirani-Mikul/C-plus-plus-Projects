#include "Polygon.h"


cCircle::cCircle(olc::vf2d pos, int verts, float radius, olc::Pixel col) : Entity(Circle::Make(verts), pos, radius, col), m_Radius(radius)
{
}

float cCircle::GetRadius() const
{
	return m_Radius;
}