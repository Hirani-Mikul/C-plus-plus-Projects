#include <iostream>
#include "olcPixelGameEngine.h"

class Game : public olc::PixelGameEngine {
public: 
	Game() {
		sAppName = "Vectors Math";
	}
private:
	struct Vector {
		float x, y;

		Vector add(Vector o) {
			return { (x + o.x), (y + o.y)};
		}

		Vector sub(Vector o) {
			return { x - o.x, y - o.y };
		}
	};

	Vector pos;
	Vector vel;
	Vector enemyPos;
	Vector dir1;
	Vector dir2;

public:

	bool OnUserCreate() override {

		//pos = { 100.0f, 50.0f };
		pos = { 0.0f, 0.0f };
		enemyPos = { 150.0f, 200.0f };
		vel = { 0.0f, 0.0f };
		

		// For Horizontal movement
		dir1 = { 0.0f, 10.0f };
		dir2 = { 10.0f, 0.0f };

		return true;
	}
	
	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::VERY_DARK_GREY);

		// Player
		FillCircle(pos.x, pos.y, 10, olc::BLUE);

		// Move Player (Horizontally)
		//pos.x = pos.x + dir1.x + dir2.x;
		//pos.y = pos.y + dir1.y + dir2.y;
		pos.x += (dir1.x + dir2.x) * fElapsedTime * 2.0f;
		pos.y += (dir1.y + dir2.y) * fElapsedTime * 2.0f;

		if (pos.x >= (float)ScreenWidth())
			pos.x = (float)ScreenWidth();
		if (pos.y >= (float)ScreenHeight())
			pos.y = (float)ScreenHeight();


		// Enemy

		FillCircle(enemyPos.x, enemyPos.y, 10, olc::RED);

		// Move enemy
		vel = pos.sub(enemyPos);
		//enemyPos = enemyPos.add(vel);
		enemyPos.x += vel.x * fElapsedTime * 5.0f;
		enemyPos.y += vel.y * fElapsedTime * 5.0f;

		return true;
	}
};

int main()
{
	Game demo;
	if (demo.Construct(300, 300, 2, 2))
		demo.Start();

}
