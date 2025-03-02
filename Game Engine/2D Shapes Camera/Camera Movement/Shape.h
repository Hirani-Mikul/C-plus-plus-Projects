#pragma once
#include "olcPixelGameEngine.h"

struct sShape
{
	static void DrawLineSegment(olc::PixelGameEngine *pge, olc::vf2d p0, olc::vf2d p1, olc::Pixel col);
	static void DrawPolygon(olc::PixelGameEngine *pge, const std::vector<olc::vf2d> &verts, const olc::vf2d &translation, float scale_x_in, float scale_y_in,  olc::Pixel col);
};


struct Star {
	
	static std::vector<olc::vf2d> Make(float outerRadius, float innerRadius, int nFlares = 5)
	{
		std::vector<olc::vf2d> star;
		star.reserve(nFlares * 2);

		const float dTheta = 2.0f * 3.14519f / (float)(nFlares * 2);

		for (int i = 0; i < nFlares * 2; i++)
		{
			const float rad = (i % 2 == 0) ? outerRadius : innerRadius;

			star.emplace_back(rad * cos((float)i * dTheta), rad * sin((float)i * dTheta));
		}

		return star;
	}

};