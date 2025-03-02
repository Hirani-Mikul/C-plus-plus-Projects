#include "Drawable.h"

Drawable::Drawable(const std::vector<olc::vf2d> &model, olc::Pixel col = olc::YELLOW) : col(col), translation(0.0f, 0.0f), fScale_X(1.0f), fScale_Y(1.0f), vecModel(&model)
{
}

void Drawable::Translate(const olc::vf2d& translation_in)
{
	translation += translation_in;
}

void Drawable::Scale(float scale_in)
{
	fScale_X *= scale_in;
	fScale_Y *= scale_in;
	translation *= scale_in;
}

void Drawable::ScaleIndependent( float scale_in_x, float scale_in_y ) {
	
	fScale_X *= scale_in_x;
	fScale_Y *= scale_in_y;
	translation.x *= scale_in_x;
	translation.y *= scale_in_y;
}

void Drawable::Render(olc::PixelGameEngine* pge) const
{
	sShape::DrawPolygon(pge, *vecModel, translation, fScale_X, fScale_Y, col);
}

