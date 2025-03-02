#pragma once
#include "olcPixelGameEngine.h"

float extern fWidth, fHeight;

class sShape {

public:
	static void DrawLineSegment(olc::PixelGameEngine* pge, olc::vf2d p0, olc::vf2d p1, olc::Pixel col);
	static void DrawPolygon(olc::PixelGameEngine* pge, std::vector<olc::vf2d>& verts, olc::vf2d pos, std::pair<float, float> size = {1.0f, 1.0f}, olc::Pixel col = olc::BLUE);

};

