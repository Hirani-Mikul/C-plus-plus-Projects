#pragma once
#include "Entity.h"

struct Camera
{
	Camera(CoordinateTransformer &ct);

	olc::vf2d GetPos() const;
	void MoveBy(const olc::vf2d& offset);
	void MoveTo(const olc::vf2d& pos_in);
	void DrawShape( Drawable &drawable ) const;

	void SetScale(float s);
	float GetScale() const;

private:

	olc::vf2d pos;
	CoordinateTransformer& ct;
	float fScale;

};

