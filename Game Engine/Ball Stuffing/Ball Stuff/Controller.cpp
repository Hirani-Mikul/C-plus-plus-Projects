#include "Controller.h"

CoordinateTransformer::CoordinateTransformer(olc::PixelGameEngine* pge) : pge(pge)
{
}

void CoordinateTransformer::DrawShape(std::vector<olc::vf2d>& model, olc::vf2d pos, std::pair<float, float> size, olc::Pixel col)
{
	olc::vf2d offset = { fWidth / 2.0f, fHeight / 2.0f};
	sShape::DrawPolygon(pge, model, pos + offset, size ,col);
}
