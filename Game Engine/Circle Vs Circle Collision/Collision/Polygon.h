#pragma once
#include "olcPixelGameEngine.h"

struct cCircle
{
	static std::vector<olc::vf2d> Make(int verts)
	{
		std::vector<olc::vf2d> tempModel;
		tempModel.reserve(verts);

		for (int i = 0; i < verts; i++)
		{
			const float radius = 1.0f;
			const float angle = ((float)i / (float)verts) * 6.28318f;
			tempModel.emplace_back(radius * sinf(angle), radius * cosf(angle));
		}

		return tempModel;
		//return std::move(tempModel);
	}
};

struct sRectangle {

	static std::vector<olc::vf2d> Make()
	{
		std::vector<olc::vf2d> tempModel;
		tempModel.reserve(4);

		tempModel.emplace_back(0.0f, 0.0f);
		tempModel.emplace_back(1.0f, 0.0f);
		tempModel.emplace_back(1.0f, -1.0f);
		tempModel.emplace_back(0.0f, -1.0f);

		return tempModel;
		
	}
};

struct sLine {
	
	static std::vector<olc::vf2d> Make( olc::vf2d p1, olc::vf2d p2 ) {

		std::vector<olc::vf2d> tempModel;
		tempModel.reserve(2);

		//tempModel.emplace_back(0.0f, 0.0f);
		//tempModel.emplace_back(0.0f, 1.0f);
		tempModel.emplace_back(p1);
		tempModel.emplace_back(p2);

		return std::move(tempModel);
	}

};
