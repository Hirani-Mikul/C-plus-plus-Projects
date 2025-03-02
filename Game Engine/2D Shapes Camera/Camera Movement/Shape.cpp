#include "Shape.h"

float extern fWidth, fHeight;

void sShape::DrawLineSegment(olc::PixelGameEngine* pge, olc::vf2d p0, olc::vf2d p1, olc::Pixel col)
{
	float m = 0.0f;

	if (p1.x != p0.x)
		m = (p1.y - p0.y) / (p1.x - p0.x);

	if (p1.x != p0.x && std::abs(m) <= 1.0f)
	{
		if (p0.x > p1.x)
			std::swap(p0, p1);

		const float c = p0.y - (m * p0.x);

		for (int x = (int)p0.x; x <= (int)p1.x; x++)
		{
			const float y = (m * (float)x) + c;

			const int nY = (int)y;

			if (x >= 0 && x < (float)pge->ScreenWidth() && nY >= 0 && nY < (float)pge->ScreenHeight())
				pge->Draw(x, nY, col);
		}
	}
	else {
		if (p0.y > p1.y)
			std::swap(p0, p1);

		const float m2 = (p1.x - p0.x) / (p1.y - p0.y);
		const float c2 = p0.x - (m2 * p0.y);

		for (int y = (int)p0.y; y <= (int)p1.y; y++)
		{
			const float x = m2 * (float)y + c2;

			const int nX = (int)x;

			if (nX >= 0 && nX < (float)pge->ScreenWidth() && y >= 0 && y < (float)pge->ScreenHeight())
				pge->Draw(nX, y, col);
		}
	}
}

void sShape::DrawPolygon(olc::PixelGameEngine* pge, const std::vector<olc::vf2d>& verts, const olc::vf2d &translation, float scale_x_in, float scale_y_in, olc::Pixel col)
{
	const auto xform = [&](olc::vf2d v)
	{
		v.x *= scale_x_in;
		v.y *= scale_y_in;
		v += translation;

		return v;
	};
	const olc::vf2d front = xform( verts.front() );
	olc::vf2d cur = front;

	for (auto i = verts.begin(); i != std::prev(verts.end()); i++)
	{
		const olc::vf2d next = xform( *std::next(i));
		DrawLineSegment(pge, cur, next, col);
		cur = next;
	}
	DrawLineSegment(pge, cur, front, col);
}

