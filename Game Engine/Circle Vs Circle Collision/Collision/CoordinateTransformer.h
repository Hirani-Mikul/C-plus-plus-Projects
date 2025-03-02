#pragma once
#include "Shape.h"

class CoordinateTransformer {

public:
	CoordinateTransformer(olc::PixelGameEngine* pge) : pge(pge) {};

public:
	void DrawPolygon( Drawable &drawable ) {
		 
		const olc::vf2d offset = { fWidth / 2.0f, fHeight / 2.0f };

		drawable.ScaleIndependent(1.0f, -1.0f);
		drawable.Translate(offset);
		drawable.Render(pge);

	}

	static void ScreenToWorld(olc::vf2d screenCoord, olc::vf2d& worldCoord)
	{
		const olc::vf2d offset = { fWidth / 2.0f, fHeight / 2.0f };

		worldCoord = screenCoord - offset;
		worldCoord.y *= -1.0f;

	}

private:
	olc::PixelGameEngine* pge;
};