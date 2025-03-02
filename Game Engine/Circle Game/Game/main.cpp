#include "CameraControls.h"
#include "Ball.h"

float fWidth, fHeight;

class Game : public olc::PixelGameEngine
{
public:
	Game() {
		sAppName = "Ball Collision Game";
	}
public:
	
	void AddStars()
	{
		for (int i = 0; i < 10; i++)
		{
			int randColIndex = Random::Get().GetRand_N(0, 4);
			int edges = Random::Get().GetRand_N2(5, 10);

			float x = Random::Get().GetRand_F2( -600, 600 );
			float y = Random::Get().GetRand_F2( -600, 600 );

			float outR = Random::Get().GetRand_F2(20, 100);
			float inR = Random::Get().GetRand_F2(20, 100);
			

			Entity star = Entity(Shape::Star::Make(outR, inR, edges), { x, y}, 1.0f, colors[randColIndex]);

			int nRotationDir = Random::Get().GetRand_N(0, 2);
			if (nRotationDir < 1)
				star.m_RotationDir = -1.0f;
			else star.m_RotationDir = 1.0f;

			stars.push_back(star);
		}
	}

	bool OnUserCreate() override {

		fWidth = (float)ScreenWidth();
		fHeight = (float)ScreenHeight();

		AddStars();
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {

		
		const olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		cam.TransformCursorCoordinates(vMouse, vCursor);

		camCtrl.Update(fElapsedTime);

		Clear(olc::VERY_DARK_GREY);

		for (auto& s : stars)
		{
			s.SetAngle(s.GetAngle() + fElapsedTime * PI / 2.0f * s.m_RotationDir);
			Drawable sd = s.GetDrawable();
			cam.DrawShape(sd);
		}
		return true;
	}

private:
	CoordinateTransformer ct = CoordinateTransformer(this);

	Camera cam = Camera(ct);
	CameraController camCtrl = CameraController(*this, cam);

	olc::vf2d vCursor = { 0.0f, 0.0f };

	olc::Pixel colors[5] = { olc::GREEN, olc::BLUE, olc::YELLOW, olc::DARK_CYAN, olc::DARK_MAGENTA };

	std::vector<Entity> stars;

};

int main()
{
	Game app;
	if (app.Construct(600, 600, 1, 1))
		app.Start();
}
