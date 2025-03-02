#pragma once
#include "Shapes.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer();
	CoordinateTransformer(olc::PixelGameEngine* pge);

	void DrawClosedPolyline(std::vector<olc::vf2d> poly, olc::Pixel col);

private:
	olc::PixelGameEngine* pge;
};

