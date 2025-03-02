#include "CameraController.h"

CameraController::CameraController(olc::PixelGameEngine& pge, Camera& cam) : pge(&pge), cam(cam), m_Engaged(false)
{
}

void CameraController::update()
{
	if (pge->GetMouse(0).bPressed)
	{
		m_Engaged = true;
		m_LastPos = olc::vf2d( (float)pge->GetMouseX(), (float)pge->GetMouseY() );
	}
	if (pge->GetMouse(0).bReleased)
		m_Engaged = false;

	if (pge->GetMouseWheel() > 0)
		cam.SetScale( cam.GetScale() * m_ZoomFactor );
	if (pge->GetMouseWheel() < 0)
		cam.SetScale(cam.GetScale() / m_ZoomFactor);

	if (m_Engaged)
	{
		const auto curPos = olc::vf2d( (float)pge->GetMouseX(), (float)pge->GetMouseY() );

		auto delta = curPos - m_LastPos;
		delta.x = -delta.x;
		cam.MoveBy( delta / cam.GetScale() );
		m_LastPos = curPos;

	}
}
