#pragma once
#include "Shape.h"

struct Drawable
{
	Drawable( const std::vector<olc::vf2d> &model, olc::Pixel col );

	void Translate( const olc::vf2d &translation_in );
	void Scale( float scale_in );
	void ScaleIndependent( float scale_in_x, float scale_in_y );

	void Render(olc::PixelGameEngine *pge) const;

private:
	olc::Pixel col;
	const std::vector<olc::vf2d>* vecModel;
	olc::vf2d translation;
	float fScale_X;
	float fScale_Y;
};

