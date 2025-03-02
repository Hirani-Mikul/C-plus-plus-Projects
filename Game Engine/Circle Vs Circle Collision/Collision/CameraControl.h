#pragma once
#include "Camera.h"

class CameraControl {
public:
	CameraControl(olc::PixelGameEngine &pge, Camera& cam) : pge(&pge), m_Cam(cam), m_Engaged(false) {
		
	};

public:

	void update() {

		if (pge->GetMouse(0).bPressed)
		{
			m_LastPos = olc::vf2d( (float)pge->GetMouseX(), (float)pge->GetMouseY() );
		}

		if (pge->GetMouse(0).bHeld)
		{
			const auto curPos = olc::vf2d((float)pge->GetMouseX(), (float)pge->GetMouseY());

			auto delta = curPos - m_LastPos;
			delta.x = -delta.x;
			m_Cam.MoveBy( delta / m_Cam.GetScale() );
			m_LastPos = curPos;
		}

		if (pge->GetMouseWheel() > 0)
		{
			m_Cam.SetScale(m_Cam.GetScale() * m_ZoomFactor);
		}

		if (pge->GetMouseWheel() < 0)
		{
			m_Cam.SetScale(m_Cam.GetScale() / m_ZoomFactor);
		}

	}

private:
	Camera& m_Cam;
	olc::PixelGameEngine* pge;
	bool m_Engaged;
	olc::vf2d m_LastPos;

	static constexpr float m_ZoomFactor = 1.05f;
};