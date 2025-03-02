#pragma once
#include "olcPixelGameEngine.h"

namespace Shape {

	struct Circle
	{
		static std::vector<olc::vf2d> Make(int verts)
		{
			std::vector<olc::vf2d> tempModel;
			tempModel.reserve(verts);

			for (int i = 0; i < verts; i++)
			{ 
				const float angle = ((float)i / (float)verts) * 6.28318f;

				tempModel.emplace_back( sinf(angle), cosf(angle) );

			}

			return std::move(tempModel);
		}
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

	struct Line {
		static std::vector<olc::vf2d> Make()
		{
			std::vector<olc::vf2d> tempModel;
			tempModel.reserve(2);

			tempModel.emplace_back(0.0f, 0.0f);
			tempModel.emplace_back(1.0f, 0.0f);

			return tempModel;
		}
	};

	struct LineSegment {
		static std::vector<olc::vf2d> Make(olc::vf2d p1, olc::vf2d p2)
		{
			std::vector<olc::vf2d> tempModel;
			tempModel.reserve(2);

			tempModel.emplace_back(p1);
			tempModel.emplace_back(p2);

			return tempModel;
		}
	};

}

