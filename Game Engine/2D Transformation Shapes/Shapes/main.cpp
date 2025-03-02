#include "Entity.h"

float fWidth, fHeight;

class Transformation : public olc::PixelGameEngine
{
public:
	Transformation()
	{
		sAppName = "2D Transformation";
	}
private:

	CoordinateTransformer ct;
	std::vector<Entity> entities;
	Camera cam = Camera(ct);


public:
	bool OnUserCreate() override {
		fWidth = (float)ScreenWidth();
		fHeight = (float)ScreenHeight();

		ct = CoordinateTransformer(this);
		entities.emplace_back(Star::Make(80.0f, 50.0f), olc::vf2d{300.0f, 0.0f});
		entities.emplace_back(Star::Make(100.0f, 50.0f), olc::vf2d{ 150.0f, 300.0f });
		entities.emplace_back(Star::Make(30.0f, 50.0f), olc::vf2d{ 250.0f, -200.0f });
		entities.emplace_back(Star::Make(20.0f, 10.0f), olc::vf2d{ -250.0f, 200.0f });
		entities.emplace_back(Star::Make(100.0f, 80.0f), olc::vf2d{ 0.0f, 0.0f });
		entities.emplace_back(Star::Make(60.0f, 50.0f), olc::vf2d{ -150.0f, 300.0f });
		entities.emplace_back(Star::Make(5.0f, 8.0f), olc::vf2d{ 400.0f, 300.0f });

		return true;
	}

	/*void moveEntities(float fElapsedTime) {
		float fSpeed = 300.0f * fElapsedTime;

		if (GetKey(olc::Key::LEFT).bHeld)
			e1.TranslateBy({ -fSpeed, 0.0f });

		if (GetKey(olc::Key::UP).bHeld)
			e1.TranslateBy({ 0.0f , fSpeed });

		if (GetKey(olc::Key::RIGHT).bHeld)
			e1.TranslateBy({ fSpeed, 0.0f });

		if (GetKey(olc::Key::DOWN).bHeld)
			e1.TranslateBy({ 0.0f , -fSpeed });
	}
	void scaleEntities(float fElapsedTime) {
		if (GetMouseWheel() > 0)
			e1.SetScale(e1.GetScale() * 1.05f);
		if (GetMouseWheel() < 0)
			e1.SetScale(e1.GetScale() * 0.95f);
		
	}*/

	void moveCamera(float fElapsedTime)
	{
		float fSpeed = 500.0f * fElapsedTime;

		if (GetKey(olc::Key::LEFT).bHeld)
			cam.MoveBy({ -fSpeed, 0.0f });

		if (GetKey(olc::Key::UP).bHeld)
			cam.MoveBy({ 0.0f , fSpeed });

		if (GetKey(olc::Key::RIGHT).bHeld)
			cam.MoveBy({ fSpeed, 0.0f });

		if (GetKey(olc::Key::DOWN).bHeld)
			cam.MoveBy({ 0.0f , -fSpeed });
	}

	void zoomCamera() {
		if (GetMouseWheel() > 0)
			cam.SetScale(cam.GetScale() * 1.05f);
		if (GetMouseWheel() < 0)
			cam.SetScale(cam.GetScale() * 0.95f);

	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		moveCamera(fElapsedTime);
		zoomCamera();

		//moveEntities(fElapsedTime);
		//scaleEntities(fElapsedTime);

		Clear(olc::VERY_DARK_GREY);

		for (auto& e : entities)
		{
			cam.DrawClosedPolyLine(e.GetPolyLine(), olc::YELLOW);
		}

		return true;
	}
};

int main()
{
	Transformation game;
	if (game.Construct(600, 600, 1, 1))
		game.Start();
}


//float angle = ((float)i / (float)verts) * 6.28318f;