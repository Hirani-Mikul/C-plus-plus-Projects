#pragma once
#include "CoordinateTransformer.h"
#include "RectF.h"

class Camera
{
public:
	Camera( CoordinateTransformer &ct );
public:
	olc::vf2d GetPos() const;
	void MoveBy(const olc::vf2d& offset);
	void MoveTo( const olc::vf2d &pos_in );
	void FollowEntity( const olc::vf2d &entity_pos );

	float GetScale()const;
	void SetScale( float scale_in );

	void DrawShape( Drawable &drawable ) const;

	RectF GetViewPortRect() const;

private:
	olc::vf2d m_Position;
	CoordinateTransformer& ct;

	float m_Scale;

};

