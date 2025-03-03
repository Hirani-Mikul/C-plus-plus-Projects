#include "Shape.h"

float extern fWidth, fHeight;

//void sShape::WrapCoordinates(float ix, float iy, float &ox, float &oy) {
//	
//	ox = ix;
//	oy = iy;
//
//	if (ix < 0.0f) ox = ix + fWidth;
//	if (ix >= fWidth) ox = ix - fWidth;
//
//	if (iy < 0.0f) oy = iy + fHeight;
//	if (iy >= fHeight) oy = iy - fHeight;
//}

void sShape::DrawLineSegment(olc::PixelGameEngine* pge, olc::vf2d point1, olc::vf2d point2, olc::Pixel col)
{
	pge->DrawString(point1, "5", olc::BLUE);

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

void sShape::DrawClosedPolyLine(olc::PixelGameEngine* pge, const std::vector<olc::vf2d>& verts, const olc::vf2d& translation_in, float scale_x_in, float scale_y_in, olc::Pixel col)
{
	auto transform = [&](olc::vf2d v)
	{
		v.x *= scale_x_in;
		v.y *= scale_y_in;
		v += translation_in;

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





