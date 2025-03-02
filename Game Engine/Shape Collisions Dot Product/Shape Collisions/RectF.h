#pragma once
#include "olcPixelGameEngine.h"

class RectF
{
public:
	RectF() = default;
	RectF( float left_in, float right_in, float top_in, float bottom_in );
	RectF( const olc::vf2d& topLeft, const olc::vf2d& bottomRight );
	RectF( const olc::vf2d& topLeft, float width, float height );

	bool IsOverLappingWith( const RectF& other ) const;
	bool IsContainedBy( const RectF& other ) const;

	static RectF FromCenter( const olc::vf2d& center, float halfWidth, float halfHeight );

	RectF GetExpanded( float offset ) const;
	olc::vf2d GetCenter() const;


public:

private:

	float m_Left;
	float m_Right;
	float m_Top;
	float m_Bottom;
};

