#pragma once
#include "olcPixelGameEngine.h"

float extern fWidth, fHeight;

struct Create {

	static void DrawLineSegment( olc::PixelGameEngine *pge, olc::vf2d p1, olc::vf2d p2, olc::Pixel col  );

	static void DrawPolygon( olc::PixelGameEngine* pge, const std::vector<olc::vf2d> &vecModel, olc::vf2d &translation_in, float sx_in, float sy_in, float angle, olc::Pixel col );
};

void Create::DrawLineSegment(olc::PixelGameEngine *pge, olc::vf2d p1, olc::vf2d p2, olc::Pixel col)
{
	float m = 0.0f;
	if (p2.x != p1.x)
		m = (p2.y - p1.y) / ( p2.x - p1.x );

	if (p2.x != p1.x && std::abs(m) <= 1.0f)
	{
		if (p1.x > p2.x)
			std::swap(p1, p2);

		const float c = p1.y - (m * p1.x);

		for (int x = (int)p1.x; x <= (int)p2.x; x++)
		{

			const float y = (m * (float)x) + c;
			const int ny = (int)y;

			if (x >= 0 && x < (int)fWidth && ny >= 0 && ny < (int)fHeight)
				pge->Draw(x, ny, col);

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
			const int nx = (int)x;

			if (nx >= 0 && nx < (int)fWidth && y >= 0 && y < (int)fHeight)
				pge->Draw(nx, y, col);
		}

	}
}


void Create::DrawPolygon(olc::PixelGameEngine* pge, const std::vector<olc::vf2d> &vecModel, olc::vf2d& translation_in, float sx_in, float sy_in, float angle, olc::Pixel col)
{
	const float cosTheta = cosf(angle);
	const float sinTheta = sinf(angle);

	auto Transform = [&](olc::vf2d v)
	{
		float newx = v.x * cosTheta - v.y * sinTheta;
		v.y = v.x * sinTheta + v.y * cosTheta;
		v.x = newx;

		v.x *= sx_in;
		v.y *= sy_in;
		v += translation_in;
		return v;
	};

	const olc::vf2d first = Transform(vecModel.front());
	olc::vf2d current = first;

	for (auto i = vecModel.begin(); i != std::prev(vecModel.end()); i ++)
	{
		olc::vf2d next = Transform(*std::next(i));
		DrawLineSegment( pge, current, next, col );
		current = next;
	}
	DrawLineSegment( pge, current, first, col );
}
