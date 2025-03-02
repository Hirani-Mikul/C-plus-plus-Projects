#pragma once
#include "Camera.h"

struct RectF
{
	RectF() = default;
	RectF( float left_in, float right_in, float top_in, float bottom_in );
	RectF( const olc::vf2d &topLeft, const olc::vf2d &bottomRight );
	RectF( const olc::vf2d &topLeft, float width, float height );

	bool IsOverLappingWith( const RectF& other ) const;
	bool IsContainedBy( const RectF& other ) const;
	static RectF FromCenter( const olc::vf2d & center, float halfWidth, float halfHeight );

	RectF GetExpanded(float offset) const;
	olc::vf2d GetCenter() const;


	float left;
	float right;
	float top;
	float bottom;
};

