#pragma once
#include "olcPixelGameEngine.h"
#include "Drawable.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer(olc::PixelGameEngine* pge) : pge{ pge } {}


public:

	void DrawShape( Drawable& drawable )
	{
		const olc::vf2d offset = { 300.0f, 300.0f };

		drawable.ScaleIndependent(1.0f, -1.0f);
		drawable.Translate(offset);

		drawable.Render(pge);
	}

private:
	olc::PixelGameEngine* pge;

};