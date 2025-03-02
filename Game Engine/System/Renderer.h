#pragma once

#include "olcPixelGameEngine.h"


struct Renderer {


	static void Draw(olc::PixelGameEngine* pge, const std::vector<olc::vf2d>& vecModels, olc::vf2d& translation, float sx, float sy, float angle, olc::Pixel color) {

		
		std::vector<olc::vf2d> vecModel = vecModels;

			/*for (int i = 0; i < vecModel.size(); i++)
	{
		vecModel[i].x = vecModel[i].x * cosf(angle) - vecModel[i].y * sinf(angle);
		vecModel[i].y = vecModel[i].x * sinf(angle) + vecModel[i].y * cosf(angle);
	}*/

			//// Scale

		/*	for (int i = 0; i < vecModel.size(); i++)
			{
				vecModel[i].x = vecModel[i].x * sx;
				vecModel[i].y = vecModel[i].y * sy;
			}

			for (int i = 0; i < vecModel.size(); i++)
			{
				vecModel[i].x = vecModel[i].x + translation.x;
				vecModel[i].y = vecModel[i].y + translation.y;
			}*/



		auto Transform = [&](olc::vf2d v) {

			//v.x = v.x * cosf(angle) - v.y * sinf(angle);
			//v.y = v.x * sinf(angle) + v.y * cosf(angle);

			v.x *= sx;
			v.y *= sy;
			v += translation;

			return v;
		};

		const olc::vf2d first = Transform(vecModel.front());
		olc::vf2d current = first;


		for (auto i = vecModel.begin(); i != std::prev(vecModel.end()); i++)
		{

			olc::vf2d next = Transform(*std::next(i));
			pge->DrawLine(current, next, color);
			current = next;
		}

		pge->DrawLine(current, first, color);

		// Rotate

		//std::vector<olc::vf2d> transformedModel;
		//int verts = vecModel.size();
		//transformedModel.resize(verts);

		//for (int i = 0; i < verts; i++)
		//{
		//	transformedModel[i].x = vecModel[i].x * cosf(angle) - vecModel[i].y * sinf(angle);
		//	transformedModel[i].y = vecModel[i].x * sinf(angle) + vecModel[i].y * cosf(angle);
		//}


		//// Scale

		//for (int i = 0; i < verts; i++) {
		//	transformedModel[i].x = transformedModel[i].x * sx;
		//	transformedModel[i].y = transformedModel[i].y * sy;
		//}

		//// Transform

		//for (int i = 0; i < verts; i++) {
		//	transformedModel[i].x = transformedModel[i].x + translation.x;
		//	transformedModel[i].y = transformedModel[i].y + translation.y;
		//}

		//// Draw

		//for (int i = 0; i < verts + 1; i++) {
		//	int j = (i + 1);

		//	pge->DrawLine(transformedModel[i % verts].x, transformedModel[i % verts].y, transformedModel[j % verts].x, transformedModel[j % verts].y, color);
		//}
	}
};