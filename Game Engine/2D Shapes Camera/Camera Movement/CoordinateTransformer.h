#pragma once
#include "Drawable.h"

struct CoordinateTransformer
{
	CoordinateTransformer(olc::PixelGameEngine *pge);

	void DrawShape( Drawable& drawable ) const;

private:
	olc::PixelGameEngine* pge;
};

