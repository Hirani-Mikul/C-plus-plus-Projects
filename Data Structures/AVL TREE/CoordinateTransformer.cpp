#include "CoordinateTransformer.h"

CoordinateTransformer::CoordinateTransformer(olc::PixelGameEngine* pge) : pge(pge)
{
}

void CoordinateTransformer::DrawShape(Drawable &drawable) const
{
	const olc::vf2d offset = { fWidth / 2.0f, fHeight / 2.0f };

	drawable.ScaleIndependent(1.0f, -1.0f);
	drawable.Translate(offset);
	drawable.Render(pge);

}
