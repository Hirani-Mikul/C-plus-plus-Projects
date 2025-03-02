#include "Shapes.h"

float extern fWidth, fHeight;

void Shapes::DrawLineSegment(olc::PixelGameEngine *pge, olc::vf2d point1, olc::vf2d point2, olc::Pixel col)
{
	float m = 0.0f;
	if (point2.x != point1.x)
	{
		m = (point2.y - point1.y) / (point2.x - point1.x);
	}

	if (point2.x != point1.x && std::abs(m) <= 1.0f)
	{
		if (point1.x > point2.x)
			std::swap(point1, point2);

		const float c = point1.y - (m * point1.x);

		for (int x = (int)point1.x; x <= (int)point2.x; x++)
		{
			const float y = (m * (float)x) + c;

			const int yi = (int)y;
			if (x >= 0 && x < fWidth && yi >= 0 && yi < fHeight)
			{
				pge->Draw(x, yi, col);
			}
		}
	}
	else {
		if (point1.y > point2.y)
			std::swap(point1, point2);

		const float m2 = (point2.x - point1.x) / (point2.y - point1.y);
		const float c2 = point1.x - m2 * point1.y;

		for (int y = (int)point1.y; y <= (int)point2.y; y++)
		{
			const float x = m2 * (float)y + c2;

			const int xi = (int)x;
			if (xi >= 0 && xi < (int)fWidth && y >= 0 && y < (int)fHeight)
			{
				pge->Draw(xi, y, col);
			}

		}

	}
}

void Shapes::DrawClosedPolyLine(olc::PixelGameEngine* pge, std::vector<olc::vf2d>& verts, olc::Pixel col)
{

	for (auto i = verts.begin(); i != std::prev(verts.end()); i++)
	{
		DrawLineSegment(pge, *i, *std::next(i), col);
	}

	DrawLineSegment(pge, verts.back(), verts.front(), col);

}




