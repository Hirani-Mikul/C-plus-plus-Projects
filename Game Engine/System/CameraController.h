#pragma once
#include "Camera.h"

class CameraController {
public:
	CameraController(olc::PixelGameEngine& pge, Camera& cam) : pge(&pge), m_Cam(cam){

	};

public:

	void update() {

		if (pge->GetMouse(0).bPressed)
		{
			m_LastPos = olc::vf2d((float)pge->GetMouseX(), (float)pge->GetMouseY());
		}

		if (pge->GetMouse(0).bHeld)
		{
			const auto curPos = olc::vf2d((float)pge->GetMouseX(), (float)pge->GetMouseY());

			auto delta = curPos - m_LastPos;
			delta.x = -delta.x;
			m_Cam.moveBy(delta / m_Cam.getScale());
			m_LastPos = curPos;
		}

		if (pge->GetMouseWheel() > 0)
		{
			m_Cam.setScale(m_Cam.getScale() * m_ZoomFactor);
		}

		if (pge->GetMouseWheel() < 0)
		{
			m_Cam.setScale(m_Cam.getScale() / m_ZoomFactor);
		}

	}

private:
	Camera& m_Cam;
	olc::PixelGameEngine* pge;
	olc::vf2d m_LastPos;

	static constexpr float m_ZoomFactor = 1.05f;
};
