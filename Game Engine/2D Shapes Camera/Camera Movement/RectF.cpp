#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in) : left(left_in), right(right_in), top(top_in), bottom(bottom_in)
{
}

RectF::RectF(const olc::vf2d& topLeft, const olc::vf2d& bottomRight) : RectF( topLeft.x, bottomRight.x, topLeft.y, bottomRight.y )
{
}

RectF::RectF(const olc::vf2d& topLeft, float width, float height) : RectF( topLeft, topLeft + olc::vf2d( width, height ) )
{
}

bool RectF::IsOverLappingWith(const RectF& other) const
{
	return right > other.left && left < other.right&& bottom > other.top && top < other.bottom;
}

bool RectF::IsContainedBy(const RectF& other) const
{
	return left >= other.left && right <= other.right && top >= other.top && bottom <= other.bottom;
}

RectF RectF::FromCenter(const olc::vf2d& center, float halfWidth, float halfHeight)
{
	const olc::vf2d half = { halfWidth, halfHeight };
	return RectF(center - half, center + half);
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF( left - offset, right + offset, top - offset, bottom + offset );
}

olc::vf2d RectF::GetCenter() const
{
	return olc::vf2d( (left + right) / 2.0f, (top + bottom) / 2.0f );
}
