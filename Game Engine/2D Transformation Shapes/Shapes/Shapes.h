#pragma once
#include "olcPixelGameEngine.h"


class Shapes
{
public:

	static void DrawLineSegment(olc::PixelGameEngine *pge, olc::vf2d point1, olc::vf2d point2, olc::Pixel col);

	static void DrawClosedPolyLine(olc::PixelGameEngine *pge, std::vector<olc::vf2d> &verts, olc::Pixel col);
};


class Star {
public:
	static std::vector<olc::vf2d> Make(float outerRadius, float innerRadius, int nFlares = 5)
	{
		std::vector<olc::vf2d> star;
		star.reserve(nFlares * 2);

		const float dTheta = 2.0f * 3.14159f / (float)(nFlares * 2);

		for (int i = 0; i < nFlares * 2; i++)
		{
			const float rad = (i % 2 == 0) ? outerRadius : innerRadius;

			star.emplace_back(rad * cos((float)i * dTheta), rad * sin((float)i * dTheta));
		}

		return star;
	}
};