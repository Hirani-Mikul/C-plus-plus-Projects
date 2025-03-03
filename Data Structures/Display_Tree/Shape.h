#pragma once

#include "olcPixelGameEngine.h"

struct Create
{
	static void Draw(olc::PixelGameEngine* pge, olc::vf2d& translation, float sx, float sy, olc::Pixel col)
	{
		float radius = 15;

		radius *= sx;

		pge->DrawString( translation, "2", col, sx);
		pge->DrawCircle(translation, radius, col);
	}
};