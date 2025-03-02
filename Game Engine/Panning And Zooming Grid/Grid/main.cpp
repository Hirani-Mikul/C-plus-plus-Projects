#include "olcPixelGameEngine.h"

/*
	ScreenX = WorldX - offSetX
	ScreenY = WorldY - offSetY

	WorldX = ScreenX + offSetX
	WorldY = ScreenY + offSetY

*/

class Grid : public olc::PixelGameEngine
{
public:
	Grid() {
		sAppName = "Panning And Zooming";
	}
private:
	float fOffsetX = 0.0f;
	float fOffsetY = 0.0f;

	float fStartPanX = 0.0f;
	float fStartPanY = 0.0f;

	float fScaleX = 1.0f;
	float fScaleY = 1.0f;

	float fSelectedCellX = 0.0f;
	float fSelectedCellY = 0.0f;

	std::vector<olc::vf2d> vSelectedCells;

	void WorldToScreen(float fWorldX, float fWorldY, int &nScreenX, int &nScreenY)
	{
		nScreenX = (int)((fWorldX - fOffsetX) * fScaleX);
		nScreenY = (int)((fWorldY - fOffsetY) * fScaleY);
	}
	void ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY)
	{
		fWorldX = (float)(nScreenX) / fScaleX + fOffsetX;
		fWorldY = (float)(nScreenY) / fScaleY + fOffsetY;
	}


public:

	bool OnUserCreate() override {

		fOffsetX = -ScreenWidth() / 2;
		fOffsetY = -ScreenHeight() / 2;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::BLACK);

		// Mouse coordinates
		float fMouseX = (float)GetMouseX();
		float fMouseY = (float)GetMouseY();

		// For panning, we need to capture the screen location when the user starts to pan
		if (GetMouse(0).bPressed)
		{
			fStartPanX = fMouseX;
			fStartPanY = fMouseY;
		}

		// ...as the mouse move, the screen location changes. Convert this screen coordinate change into world coordinates to implement the pan.

		if (GetMouse(0).bHeld)
		{
			fOffsetX -= (fMouseX - fStartPanX) / fScaleX;
			fOffsetY -= (fMouseY - fStartPanY) / fScaleY;

			// start "new" pan for next epoch

			fStartPanX = fMouseX;
			fStartPanY = fMouseY;
		}

		float fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom;

		ScreenToWorld(fMouseX, fMouseY, fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom);

		if (GetMouseWheel() > 0 || GetKey(olc::Key::Z).bHeld)
		{
			fScaleX *= 1.001f;
			fScaleY *= 1.001f;
		}
		if (GetMouseWheel() < 0 || GetKey(olc::Key::X).bHeld)
		{
			fScaleX *= 0.999f;
			fScaleY *= 0.999f;
		}

		float fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom;

		ScreenToWorld(fMouseX, fMouseY, fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom);

		fOffsetX += (fMouseWorldX_BeforeZoom - fMouseWorldX_AfterZoom);
		fOffsetY += (fMouseWorldY_BeforeZoom - fMouseWorldY_AfterZoom);

		if (GetMouse(1).bReleased)
		{
			fSelectedCellX = (int)fMouseWorldX_AfterZoom;
			fSelectedCellY = (int)fMouseWorldY_AfterZoom;

			vSelectedCells.push_back({ fSelectedCellX, fSelectedCellY });
		}

		float fWorldLeft, fWorldTop, fWorldRight, fWorldBottom;
		ScreenToWorld(0, 0, fWorldLeft, fWorldTop);
		ScreenToWorld(ScreenWidth(), ScreenHeight(), fWorldRight, fWorldBottom);

		int nLinesDrawn = 0;

		// Horizontal lines 10
		for (float y = 0.0f; y <= 10.0f; y++)
		{
			if (y >= fWorldTop && y <= fWorldBottom)
			{

				float fStartX = 0.0f, fStartY = y;
				float fEndX = 10.0f, fEndY = y;

				int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

				WorldToScreen(fStartX, fStartY, pixel_sx, pixel_sy);
				WorldToScreen(fEndX, fEndY, pixel_ex, pixel_ey);

				DrawLine(pixel_sx, pixel_sy, pixel_ex, pixel_ey, olc::WHITE);
				nLinesDrawn++;
			}
		}

		// Vertical lines 10
		for (float x = 0.0f; x <= 10.0f; x++)
		{
			if (x >= fWorldLeft && x <= fWorldRight)
			{
				float fStartX = x, fStartY = 0.0f;
				float fEndX = x, fEndY = 10.0f;

				int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

				WorldToScreen(fStartX, fStartY, pixel_sx, pixel_sy);
				WorldToScreen(fEndX, fEndY, pixel_ex, pixel_ey);

				DrawLine(pixel_sx, pixel_sy, pixel_ex, pixel_ey, olc::WHITE);
				nLinesDrawn++;
			}
		}

		//int cx, cy, cr;
		//WorldToScreen(fSelectedCellX + .5f, fSelectedCellY + .5f, cx, cy);

		std::vector<olc::vi2d> vCells;
		//vCells.resize(vSelectedCells.size());

		for (int i = 0; i < vSelectedCells.size(); i++)
		{
			//int cx, cy, cr;
			int cx, cy;
			WorldToScreen(vSelectedCells[i].x + .5f, vSelectedCells[i].y +.5f, cx, cy);
			vCells.push_back({ cx, cy });
		}
		/*if (GetMouse(1).bReleased)
		{
			vSelectedCells.push_back({ cx, cy });
		}*/

		int cr = .3f * fScaleX;

		//FillCircle(cx, cy, cr, olc::RED);
		for (int i = 0; i < vCells.size(); i++)
		{
			FillCircle(vCells[i], cr, olc::RED);
		}

		//DrawString(5, 5, std::to_string(nLinesDrawn), olc::GREEN, 1U);
		DrawString(10, 10, "Line: " + std::to_string(nLinesDrawn), olc::GREEN);

		return true;
	}
};

int main() {

	Grid draw;
	if (draw.Construct(300, 300, 2, 2))
		draw.Start();
}

