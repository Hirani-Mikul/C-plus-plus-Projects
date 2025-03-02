#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in) : m_Left(left_in), m_Right(right_in), m_Top(top_in), m_Bottom(bottom_in)
{
}

RectF::RectF(const olc::vf2d& topLeft, const olc::vf2d& bottomRight)
	: RectF( topLeft.x, bottomRight.x, topLeft.y, bottomRight.y )
{
}

RectF::RectF(const olc::vf2d& topLeft, float width, float height) : RectF(topLeft, topLeft + olc::vf2d{ width, height })
{
}

bool RectF::IsOverLappingWith(const RectF& other) const
{
	return m_Right > other.m_Left && m_Left < other.m_Right&& m_Bottom > other.m_Top && m_Top < other.m_Bottom;
}

bool RectF::IsContainedBy(const RectF& other) const
{
	return m_Left >= other.m_Left && m_Right <= other.m_Right && m_Top >= other.m_Top && m_Bottom <= other.m_Bottom;
}

RectF RectF::FromCenter(const olc::vf2d& center, float halfWidth, float halfHeight)
{
	const olc::vf2d half = { halfWidth, halfHeight };

	return RectF( center - half, center + half );

}

RectF RectF::GetExpanded(float offset) const
{
	return RectF( m_Left - offset, m_Right +offset, m_Top - offset, m_Bottom + offset );
}

olc::vf2d RectF::GetCenter() const
{
	return olc::vf2d( (m_Left + m_Right) / 2.0f, (m_Top + m_Bottom) / 2.0f );
}
