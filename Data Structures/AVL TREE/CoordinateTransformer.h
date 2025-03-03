#pragma once
#include "Shape.h"
#include "Drawable.h"

float extern fWidth, fHeight;

class CoordinateTransformer
{
public:
	CoordinateTransformer( olc::PixelGameEngine *pge );

	void DrawShape( Drawable &drawable ) const;

private:
	olc::PixelGameEngine* pge;
};

