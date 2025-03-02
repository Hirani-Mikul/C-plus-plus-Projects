#include "CoordinateTransformer.h"

float extern fWidth, fHeight;

CoordinateTransformer::CoordinateTransformer(olc::PixelGameEngine* pge) : pge(pge) {}

void CoordinateTransformer::DrawShape( Drawable& drawable) const
{
	const olc::vf2d offset = { fWidth / 2, fHeight / 2 };

	drawable.ScaleIndependent(1.0f, -1.0f);
	drawable.Translate(offset);
	drawable.Render(pge);

}
