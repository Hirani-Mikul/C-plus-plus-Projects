#pragma once
#include "olcPixelGameEngine.h"

float extern fWidth, fHeight;

void WrapCoordinates(float ix, float iy, float &ox, float &oy)
{
	ox = ix;
	oy = iy;

	if (ix < 0.0f) ox = ix + fWidth;
	if (ix >= fWidth) ox = ix - fWidth;

	if (iy < 0.0f) oy = iy + fHeight;
	if (iy >= fHeight) oy = iy - fHeight;
}

struct sShape {


	static void DrawLineSegment( olc::PixelGameEngine*pge, olc::vf2d p1, olc::vf2d p2,  olc::Pixel col);
	static void DrawPolygon(olc::PixelGameEngine *pge, const std::vector<olc::vf2d> &verts, olc::vf2d &translation, float sx, float sy, olc::Pixel col);

};
void sShape::DrawLineSegment(olc::PixelGameEngine* pge, olc::vf2d p1, olc::vf2d p2, olc::Pixel col) {

	float m = 0.0f;
	if (p2.x != p1.x)
		m = (p2.y - p1.y) / (p2.x - p1.x);

	if (p2.x != p1.x && std::abs(m) <= 1.0f)
	{
		if (p1.x > p2.x)
			std::swap(p1, p2);

		const float c = p1.y - (m * p1.x);

		for (int x = (int)p1.x; x <= (int)p2.x; x++)
		{
			const float y = (m * (float)x) + c;

			const int nY = (int)y;

			if (x >= 0 && x < (int)fWidth && nY >= 0 && nY < (int)fHeight)
				pge->Draw(x, nY, col);
		}

	}
	else {
		if (p1.y > p2.y)
			std::swap(p1, p2);

		const float m2 = (p2.x - p1.x) / (p2.y - p1.y);
		const float c2 = p1.x - m2 * p1.y;

		for (int y = (int)p1.y; y <= (int)p2.y; y++)
		{
			const float x = m2 * (float)y + c2;
			const int nX = (int)x;

			if (nX >= 0 && nX < (int)fWidth && y >= 0 && y < (int)fHeight)
				pge->Draw(nX, y, col);
		}
	}

}

void sShape::DrawPolygon(olc::PixelGameEngine* pge, const std::vector<olc::vf2d>& verts, olc::vf2d& translation, float sx, float sy, olc::Pixel col) {

	auto transform = [&](olc::vf2d v)
	{
		v.x *= sx;
		v.y *= sy;
		v += translation;

		return v;
	};

	const olc::vf2d front = transform(verts.front());
	olc::vf2d current = front;

	for (auto i = verts.begin(); i != std::prev(verts.end()); i++)
	{ 
		olc::vf2d next = transform(*std::next(i));
		DrawLineSegment(pge, current, next, col);
		current = next;
	}
	DrawLineSegment(pge, current, front, col);

}

