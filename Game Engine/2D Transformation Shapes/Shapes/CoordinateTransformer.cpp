#include "CoordinateTransformer.h"

float extern fWidth, fHeight;

CoordinateTransformer::CoordinateTransformer() : pge(nullptr) {}
CoordinateTransformer::CoordinateTransformer(olc::PixelGameEngine *pge) : pge(pge) {}

void CoordinateTransformer::DrawClosedPolyline(std::vector<olc::vf2d> poly, olc::Pixel col)
{
	olc::vf2d offSet = { fWidth / 2.0f, fHeight / 2.0f };

	for (auto& v : poly)
	{
		v.y *= -1.0f;
		v += offSet;
	}

	Shapes::DrawClosedPolyLine(pge, poly, col);
	
}
