#pragma once
#include "Camera.h"
#include "olcPixelGameEngine.h"

class CameraController {
	
public:
	CameraController( olc::PixelGameEngine &pge, Camera &cam ) : pge(pge), cam(cam){}
public:

	void Update( float fElapsedTime ) {

		if (pge.GetKey(olc::Key::Q).bHeld) {
			
			cam.SetAngle(cam.GetAngle() + m_RotationSpeed * fElapsedTime);
		}
		else if (pge.GetKey(olc::Key::E).bHeld) {

			cam.SetAngle(cam.GetAngle() - m_RotationSpeed * fElapsedTime);
		}
		
		
		if (pge.GetKey(olc::Key::LEFT).bHeld)
		{
			olc::vf2d offset = { -fElapsedTime * m_MovementSpeed, 0.0f };
			cam.MoveBy( GetRotated(-offset, -cam.GetAngle()) );
		} 
		else if (pge.GetKey(olc::Key::RIGHT).bHeld)
		{
			olc::vf2d offset = { fElapsedTime * m_MovementSpeed, 0.0f };
			cam.MoveBy( GetRotated(-offset, -cam.GetAngle()) );
		}
		if (pge.GetKey(olc::Key::UP).bHeld)
		{
			olc::vf2d offset = { 0.0f, fElapsedTime * m_MovementSpeed };
			cam.MoveBy(GetRotated(-offset, -cam.GetAngle()));
		}
		else if (pge.GetKey(olc::Key::DOWN).bHeld)
		{
			olc::vf2d offset = { 0.0f, -fElapsedTime * m_MovementSpeed };
			cam.MoveBy(GetRotated(-offset, -cam.GetAngle()));
		}
		
		if (pge.GetMouse(0).bPressed)
			m_LastPos = olc::vf2d( (float)pge.GetMouseX(), (float)pge.GetMouseY() );

		if (pge.GetMouse(0).bHeld)
		{

			const auto curPos = olc::vf2d((float)pge.GetMouseX(), (float)pge.GetMouseY());

			auto delta = curPos - m_LastPos;
			delta.x = -delta.x;
			delta = GetRotated( delta, -cam.GetAngle() );

			cam.MoveBy( delta / cam.GetScale() );
			m_LastPos = curPos;
		}

		if (pge.GetMouseWheel() < 0)
			cam.SetScale(cam.GetScale() / m_ZoomFactor);

		if (pge.GetMouseWheel() > 0)
			cam.SetScale( cam.GetScale() * m_ZoomFactor );

	}

private:
	olc::PixelGameEngine& pge;
	Camera& cam;

	olc::vf2d m_LastPos;

	static constexpr float m_ZoomFactor = 1.05f;
	static constexpr float m_RotationSpeed = PI / 6.0f;
	static constexpr float m_MovementSpeed = 600.0f;
};
