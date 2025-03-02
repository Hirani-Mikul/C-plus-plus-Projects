#pragma once
//#include "olcPixelGameEngine.h"
#include "Camera.h"

class Engine : public olc::PixelGameEngine
{
public:
	Engine() {
		sAppName = "2D Shapes And Transformation";
	}
public:

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void MoveCamera(float fElapsedTime, olc::vf2d vMouse);

private:
	CoordinateTransformer ct = CoordinateTransformer(this);
	Camera cam = Camera(ct);

	olc::vf2d vStartPan = { 0.0f, 0.0f };
	olc::vf2d offset = { (float)ScreenWidth() / 2, (float)ScreenHeight() / 2 };
};

