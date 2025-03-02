#pragma once
#include "Entity.h"
#include "Polygon.h"

class Plank : public Entity
{
public:
	Plank( olc::vf2d pos, float radius, float length, olc::Pixel col = olc::RED ) : Entity(sRectangle::Make(), pos, radius, col), fLength(length) {}

public:

	Drawable GetDrawable() const
	{
		Drawable d(m_Model, m_Col);
		d.ScaleIndependent(m_Radius, fLength);
		d.Scale(m_Scale);
		d.Translate(m_Position);

		return d;
	}
	bool IsInsideRect(olc::vf2d other)
	{
		return other.x >= m_Position.x && other.x <= m_Position.x + m_Radius && other.y >= m_Position.y && other.y < m_Position.y - m_Radius;
	}

	void MoveSelectedEnd(olc::vf2d cursor)
	{
		m_Position = cursor;
	}

private:
	float fLength;
	
	std::pair<olc::vf2d*, olc::vf2d*> m_SelectedEnd;
};