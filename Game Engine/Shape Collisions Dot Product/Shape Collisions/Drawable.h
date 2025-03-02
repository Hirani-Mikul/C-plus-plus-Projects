#pragma once
#include "Shape.h"

class Drawable
{
public:
	Drawable( const std::vector<olc::vf2d> &model, olc::Pixel col );

public:
	void Translate( const olc::vf2d &translation_in );
	void Scale( float scale_in );
	void ScaleIndependent(float scale_x_in, float scale_y_in);
	void Render(olc::PixelGameEngine* pge);
	

private:
	const std::vector<olc::vf2d>* m_Model;
	olc::vf2d m_Translation;
	float m_Scale_x;
	float m_Scale_y;
	olc::Pixel m_Col;
};

