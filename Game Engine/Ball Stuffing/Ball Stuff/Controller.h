#pragma once
#include "Shape.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer(olc::PixelGameEngine *pge);

	void DrawShape(std::vector<olc::vf2d>& model, olc::vf2d pos, std::pair<float, float> size, olc::Pixel col = olc::BLUE);

private:
	olc::PixelGameEngine* pge;
};

