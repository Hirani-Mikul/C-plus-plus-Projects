#pragma once
#include "Camera.h"

class CameraController
{
public:
	CameraController(olc::PixelGameEngine &pge, Camera &cam);
	
public:
	void update();


private:
	static constexpr float m_ZoomFactor = 1.05f;
	olc::PixelGameEngine* pge;
	bool m_Engaged;
	olc::vf2d m_LastPos;
	Camera& cam;
};

