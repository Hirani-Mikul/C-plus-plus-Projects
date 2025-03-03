#pragma once
#include "olcPixelGameEngine.h"

struct sShape
{
	static void WrapCoordinates(float ix, float iy, float& ox, float& oy);

	static void DrawLineSegment(olc::PixelGameEngine* pge, olc::vf2d point1, olc::vf2d point2, olc::Pixel col);

	static void DrawClosedPolyLine(olc::PixelGameEngine* pge, const std::vector<olc::vf2d>& verts, const olc::vf2d &translation_in, float scale_x_in, float scale_y_in, olc::Pixel col);

};


struct Circle {

	static std::vector<olc::vf2d> Make(int verts) {
		std::vector<olc::vf2d> tempModel;
		tempModel.reserve(verts);

		for (int i = 0; i < verts; i++)
		{
			float radius = 1.0f;
			float angle = ((float)i / (float)verts) * 6.28318f;
			tempModel.emplace_back(radius * sinf(angle), radius * cosf(angle));
		}

		return tempModel;
	};
};

struct Rectangle {
	
	static std::vector<olc::vf2d> Make() {

		std::vector<olc::vf2d> tempModel;
		tempModel.reserve(4);

		tempModel.emplace_back(0.0f, 0.0f);
		tempModel.emplace_back(1.0f, 0.0f);
		tempModel.emplace_back(1.0f, 1.0f);
		tempModel.emplace_back(0.0f, 1.0f);

		return tempModel;

	}
};