#include "Platform.h"

class Game : public olc::PixelGameEngine {

public:
	Game() {
		sAppName = "Platform Ball";
	}

private:
	std::vector<Platform> Walls;
	std::vector<Platform> Surfaces;
	std::vector<std::pair<olc::vf2d, olc::vf2d>> vWallProps;

	Ball b;
	std::vector<Ball> balls;
	float fScreenW;
	float fScreenH;

	olc::vf2d f;
	olc::vf2d f2;

public:

	void createWalls() {

		Walls.reserve(4);
		vWallProps.reserve(4);
		vWallProps.emplace_back(std::make_pair(olc::vf2d{ 5.0f, fScreenH / 2.0f }, olc::vf2d{ 10.0f, fScreenH - 20.0f })); // LEFT
		vWallProps.emplace_back(std::make_pair(olc::vf2d{ fScreenW / 2.0f, 5.0f }, olc::vf2d{ fScreenW, 10.0f })); // TOP
		vWallProps.emplace_back(std::make_pair(olc::vf2d{ fScreenW - 5.0f, fScreenH / 2.0f }, olc::vf2d{ 10.0f, fScreenH - 20.0f })); // RIGHT
		vWallProps.emplace_back(std::make_pair(olc::vf2d{ fScreenW / 2.0f, fScreenH - 5.0f }, olc::vf2d{ fScreenW, 10.0f })); // Ground


		for (int i = 0; i < 4; i++)
		{
			Walls.emplace_back(vWallProps[i].first, vWallProps[i].second.x, vWallProps[i].second.y);
		}
	}


	bool OnUserCreate() override {

		fScreenW = (float)ScreenWidth();
		fScreenH = (float)ScreenHeight();

		f = { 2000.0f, -2000.0f };
		f2 = { -2000.0f, -2000.0f };


		createWalls();

		Surfaces.push_back(Platform({ 50.0f, 230.0f }, 50.0f, 10.0f));
		Surfaces.push_back(Platform({ 200.0f, 190.0f }, 80.0f, 10.0f));

		//b = Ball({fScreenW / 2.0f, fScreenH / 2.0f}, 20.0f);

		for (int i = 0; i < 1; i++)
		{
			float bx = 50.0f + (rand() % 200);
			float by = 50.0f + (rand() % 200);
			float br = 10.0f + (rand() % 15);
			int id = rand() % int(bx + by);
			balls.push_back(Ball({ bx, by } , 15.0f, id));
		}


		return true;
	}

	void addBalls() {
		if (GetKey(olc::Key::SPACE).bPressed)
		{
			int id = rand() % int(GetMouseX() + GetMouseY());
			balls.push_back(Ball({(float)GetMouseX(), (float)GetMouseY()}, 15.0f, id));
		}
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::VERY_DARK_GREY);

		// Draw Walls
		for (auto& w : Walls)
		{
			w.display(*this);
		}
		for (auto& s : Surfaces)
		{
			s.display(*this);
		}

		//if (GetKey(olc::Key::LEFT).bHeld)
		//{
		//	b.applyForce(f2);
		//}
		//else if (GetKey(olc::Key::RIGHT).bHeld)
		//	b.applyForce(f);

		//b.checkWalls(Walls);
		//b.update(fElapsedTime);
		//b.display(*this);


		for (auto& b : balls)
		{
			if (GetKey(olc::Key::LEFT).bHeld)
			{
				b.applyForce(f2);
			}
			else if (GetKey(olc::Key::RIGHT).bHeld)
			{
				b.applyForce(f);
			}
			b.checkPlatforms(Surfaces);
			b.checkWalls(Walls);
			b.update(fElapsedTime);
			b.display(*this);
		}

		for (int i = 0; i < balls.size(); i++)
		{
			for (int j = 0; j < balls.size(); j++)
			{
				if (balls[i].bId != balls[j].bId && balls[i].intersects(balls[j]))
				{
					balls[i].bounce(balls[j]);
					balls[i].col = olc::VERY_DARK_GREEN;
					balls[j].col = olc::VERY_DARK_GREEN;
				}
				else {
					balls[i].col = olc::BLUE;
					balls[j].col = olc::BLUE;

				}
			}
		}

		addBalls();


		return true;
	}
};

int main() {
	Game game;
	if (game.Construct(300, 300, 2, 2))
		game.Start();
}

void DrawGameObjects(olc::PixelGameEngine& pge, std::vector<olc::vf2d>& vecModelCoordinates, olc::vf2d vecPos, float angle = 0.04f, float scale = 1.0f, olc::Pixel col = olc::WHITE) {

	std::vector<olc::vf2d> vecTransformedCoordinate;
	int verts = vecModelCoordinates.size();
	vecTransformedCoordinate.resize(verts);

	// Rotate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinate[i].x = vecModelCoordinates[i].x * cosf(angle) - vecModelCoordinates[i].y * sinf(angle);
		vecTransformedCoordinate[i].y = vecModelCoordinates[i].x * sinf(angle) + vecModelCoordinates[i].y * cosf(angle);
	}

	// Scale
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinate[i].x *= scale;
		vecTransformedCoordinate[i].y *= scale;
	}

	// Translate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinate[i].x += vecPos.x;
		vecTransformedCoordinate[i].y += vecPos.y;
	}

	// Draw
	for (int i = 0; i < verts + 1; i++)
	{
		int j = (i + 1);

		pge.DrawLine(vecTransformedCoordinate[i % verts].x, vecTransformedCoordinate[i % verts].y, vecTransformedCoordinate[j % verts].x, vecTransformedCoordinate[j % verts].y, col);
	}

}

void DrawGameObjectsRect(olc::PixelGameEngine& pge, std::vector<olc::vf2d>& vecModelCoordinates, olc::vf2d vecPos, float angle = 0.04f, float scaleX = 1.0f, float scaleY = 1.0f, olc::Pixel col = olc::WHITE) {

	std::vector<olc::vf2d> vecTransformedCoordinate;
	int verts = vecModelCoordinates.size();
	vecTransformedCoordinate.resize(verts);

	float fMiddle = 0.5f;

	// Rotate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinate[i].x = (vecModelCoordinates[i].x - fMiddle) * cosf(angle) - (vecModelCoordinates[i].y - fMiddle) * sinf(angle);
		vecTransformedCoordinate[i].y = (vecModelCoordinates[i].x - fMiddle) * sinf(angle) + (vecModelCoordinates[i].y - fMiddle) * cosf(angle);
	}

	// Scale
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinate[i].x *= scaleX;
		vecTransformedCoordinate[i].y *= scaleY;
	}

	// Translate
	for (int i = 0; i < verts; i++)
	{
		vecTransformedCoordinate[i].x += vecPos.x;
		vecTransformedCoordinate[i].y += vecPos.y;
	}

	// Draw
	for (int i = 0; i < verts + 1; i++)
	{
		int j = (i + 1);

		pge.DrawLine(vecTransformedCoordinate[i % verts].x, vecTransformedCoordinate[i % verts].y, vecTransformedCoordinate[j % verts].x, vecTransformedCoordinate[j % verts].y, col);
	}

}

void limit(olc::vf2d &v, float max) {

	const float mSq = v.mag2();

	if (mSq > max * max)
	{
		v /= sqrt(mSq);
		v *= max;
	}
}
float dist(float x, float y, float ox, float oy) {
	return hypotf(ox - x, oy - y);
}