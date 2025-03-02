#pragma once
#include "olcPixelGameEngine.h"

struct Create {

	static void Draw( olc::PixelGameEngine* pge, const std::vector<olc::vf2d>& vecModel, olc::vf2d& translation, float sx, float sy, olc::Pixel col )
	{
		auto Transform = [&]( olc::vf2d v )
		{
			v.x *= sx;
			v.y *= sy;
			v += translation;
			return v;

		};

		const auto first = Transform(vecModel.front());
		olc::vf2d current = first;

		for (auto i = vecModel.begin(); i != std::prev(vecModel.end()); i++)
		{
			olc::vf2d next = Transform(*std::next(i));
			pge->DrawLine(current, next, col);
			current = next;
		}

		pge->DrawLine(current, first, col);

	}

};

namespace Shape {

	struct Ellipse {

		static std::vector<olc::vf2d> Make( int verts = 20 )
		{
			//6.28318f;
			std::vector<olc::vf2d> tempModel;
			tempModel.reserve(verts);

			for (int i = 0; i < verts; i++)
			{
				float radius = 1.0f;
				float angle = ((float)i / (float)verts) * 6.28318f;
				tempModel.emplace_back( radius * sinf(angle), radius * cosf(angle) );
			}

			return std::move(tempModel);

		}

	};

	struct Rect {
		static std::vector<olc::vf2d> Make()
		{
			std::vector<olc::vf2d> tempModel;
			tempModel.reserve(4);

			tempModel.emplace_back(-0.5f, -0.5f);
			tempModel.emplace_back(0.5f, -0.5f);
			tempModel.emplace_back(0.5f, 0.5f);
			tempModel.emplace_back(-0.5f, 0.5f);

			return std::move(tempModel);
		}
	};

	struct FillRect {

		static std::vector<olc::vf2d> Make()
		{
			std::vector<olc::vf2d> tempModel;

			for (int i = 0; i < 4; i++)
			{

				for (float i = -0.5f; i <= 0.5f; i += 0.01f)
				{
					for (float j = -0.5f; j <= 0.5f; j += 0.01f)
						tempModel.push_back({ j, i });
				}
			}

			return std::move(tempModel);
		}

	};

}

