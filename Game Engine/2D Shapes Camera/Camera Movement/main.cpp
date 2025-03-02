#include "Game.h"

float fWidth, fHeight;

bool Engine::OnUserCreate() {
	fWidth = (float)ScreenWidth();
	fHeight = (float)ScreenHeight();

	return true;
}

void Engine::MoveCamera(float fElapsedTime, olc::vf2d vMouse)
{
	float fSpeed = 500.0f;
	fSpeed *= fElapsedTime;

	olc::vf2d prevPos;
	if (GetMouse(0).bPressed)
		vStartPan = vMouse;
	if (GetMouse(0).bHeld)
	{
		offset = (vStartPan - vMouse) * fSpeed;
		cam.MoveBy(offset);
		vStartPan = vMouse;
	}

	if (GetKey(olc::Key::Z).bHeld)
		cam.SetScale(cam.GetScale() * 1.005f);
	if (GetKey(olc::Key::X).bHeld)
		cam.SetScale(cam.GetScale() * 0.995f);

	if (GetKey(olc::Key::LEFT).bHeld)
		cam.MoveBy({ -fSpeed, 0.0f });
	if (GetKey(olc::Key::UP).bHeld)
		cam.MoveBy({ 0.0f, fSpeed });
	if (GetKey(olc::Key::RIGHT).bHeld)
		cam.MoveBy({ fSpeed, 0.0f });
	if (GetKey(olc::Key::DOWN).bHeld)
		cam.MoveBy({ 0.0f , -fSpeed });
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
	olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

	Clear(olc::VERY_DARK_GREY);

	MoveCamera(fElapsedTime, vMouse);
	
	std::string txtX = std::to_string(cam.GetPos().x);
	std::string txtY = std::to_string(cam.GetPos().y);
	std::string txtS = std::to_string(cam.GetScale());

	DrawString({10, 5}, txtX + ", " + txtY + " || " + txtS, olc::YELLOW);
	return true;
}


int main() {

	Engine game;
	if (game.Construct(600, 600, 1, 1))
		game.Start();
}