#include "olcPixelGameEngine.h"

class Asteroid : public olc::PixelGameEngine {

public:
	Asteroid() {
		sAppName = "Asteroid Game";
	}
private:
	float damping = 0.999f;
	struct sSpaceObject {

		float x;
		float y;
		float dx;
		float dy;
		float fSpeed;
		int nSize;
		float angle;
	};

	std::vector<sSpaceObject> vecAsteroids;
	std::vector<sSpaceObject> vecBullets;
	sSpaceObject player;
	bool bDead = false;
	int nScore = 0;

	std::vector<std::pair<float, float>> vecModelShip;
	std::vector<std::pair<float, float>> vecModelAsteroid;

	bool OnUserCreate() override {

		vecModelShip = {
			{ 0.0f, -5.0f },
			{ -2.5f, +2.5f },
			{ +2.5f, +2.5f }
		}; // Isoceles Triangle

		// Asteroid

		int verts = 20;

		for (int i = 0; i < verts; i++) {

			//float radius = 1.0f;
			float radius = (float)rand() / (float)RAND_MAX * 0.4f + 0.8f;
			float a = ((float)i / (float)verts) * 6.28318f;
			vecModelAsteroid.push_back(std::make_pair(radius * sinf(a), radius * cosf(a)));
		}

		ResetGame();

		return true;
	}

	bool IsPointInsideCircle(float cx, float cy, float radius, float x, float y)
	{
		return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
	}

	void ResetGame() {

		vecAsteroids.clear();
		vecBullets.clear();

		vecAsteroids.push_back({ 20.0f, 20.0f, 8.0f, -6.0f, 4.0f, (int)32, 0.0f });
		vecAsteroids.push_back({ 100.0f, 20.0f, -5.0f, 3.0f, 4.0f, (int)32, 0.0f });

		// Initialise Player Position
		player.x = ScreenWidth() / 2.0f;
		player.y = ScreenHeight() / 2.0f;
		player.dx = 0.0f;
		player.dy = 0.0f;
		player.angle = 0.0f;
		player.fSpeed = 3.0f;

		bDead = false;
		nScore = 0;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		// Reset the game
		if (bDead)
			ResetGame();

		// Clear the screen
		Clear(olc::BLACK);

		// Steer
		if (GetKey(olc::Key::LEFT).bHeld)
			player.angle -= 5.0f * fElapsedTime;
		if (GetKey(olc::Key::RIGHT).bHeld)
			player.angle += 5.0f * fElapsedTime;

		// Thrust
		if (GetKey(olc::Key::UP).bHeld)
		{
			// Acceleration added to velocity
			player.dx += sin(player.angle) * 20.0f * fElapsedTime;
			player.dy += -cos(player.angle) * 20.0f * fElapsedTime;
		}
		else {
			player.dx *= damping;
			player.dy *= damping;
		}

		// Updating position based on velocity
		player.x += player.dx * fElapsedTime * player.fSpeed;
		player.y += player.dy * fElapsedTime * player.fSpeed;

		// Keep ship in gamespace (Wrap)
		WrapCoordinates(player.x, player.y, player.x, player.y);

		// Check ship collision with asteroids
		for (auto& a : vecAsteroids)
			if (IsPointInsideCircle(a.x, a.y, a.nSize, player.x, player.y))
				bDead = true;

		// Fire bullets in direction of player
		if (GetKey(olc::Key::SPACE).bReleased)
			vecBullets.push_back({ player.x, player.y, 50.0f * sinf(player.angle), -50.0f * cosf(player.angle), 0, 0 });

		for (auto& a : vecAsteroids)
		{
			a.x += a.dx * fElapsedTime * a.fSpeed;
			a.y += a.dy * fElapsedTime * a.fSpeed;

			a.angle += 0.5f * fElapsedTime;
			WrapCoordinates(a.x, a.y, a.x, a.y);
			DrawWireFrameModel(vecModelAsteroid, a.x, a.y, a.angle, a.nSize, olc::YELLOW);
			
		}

		std::vector<sSpaceObject> newAsteroids;

		for (auto& b : vecBullets)
		{
			b.x += b.dx * fElapsedTime * 3.0f;
			b.y += b.dy * fElapsedTime * 3.0f;

			WrapCoordinates(b.x, b.y, b.x, b.y);
			Draw(b.x, b.y, olc::BLUE);

			// Check collision with asteroids
			for (auto& a : vecAsteroids)
			{
				if (IsPointInsideCircle(a.x, a.y, a.nSize, b.x, b.y))
				{
					// Asteroid hit
					b.x = -100;

					if (a.nSize > 4)
					{
						// Create two child asteroids
						float angle1 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
						float angle2 = ((float)rand() / (float)RAND_MAX) * 6.283185f;
						newAsteroids.push_back({a.x, a.y, 10.0f * sinf(angle1), 10.0f * cosf(angle1), 4.0f, (int)a.nSize >> 1, 0.0f});
						newAsteroids.push_back({ a.x, a.y, 10.0f * sinf(angle2), 10.0f * cosf(angle2), 4.0f ,(int)a.nSize >> 1, 0.0f });
					}

					a.x = -100.0f; 
					nScore += 100;
				}
			}
		}

		// Append new asteroids to existing vector
		for (auto a : newAsteroids)
			vecAsteroids.push_back(a);

		// Remove off screen bullets
		if (vecBullets.size() > 0) {
			auto i = std::remove_if(vecBullets.begin(), vecBullets.end(), [&](sSpaceObject o) {return (o.x < 1 || o.y < 1 || o.x >= ScreenWidth() || o.y >= ScreenHeight()); });

			if (i != vecBullets.end())
				vecBullets.erase(i);
		}
		// Remove off screen hit asteroids
		if (vecAsteroids.size() > 0) {
			auto i = std::remove_if(vecAsteroids.begin(), vecAsteroids.end(), [&](sSpaceObject o) {return (o.x < 0.0f); });

			if (i != vecAsteroids.end())
				vecAsteroids.erase(i);
		}

		if (vecAsteroids.empty())
		{
			nScore += 1000;

			vecAsteroids.push_back(
				{
					30.0f * sinf(player.angle - 3.14159f / 2.0f),
					30.0f * cosf(player.angle - 3.14159f / 2.0f),
					10.0f * sinf(player.angle),
					10.0f * cosf(player.angle),
					3.0f,
					(int)32, 0.0f
				}
			);
			vecAsteroids.push_back(
				{
					30.0f * sinf(player.angle + 3.14159f / 2.0f),
					30.0f * cosf(player.angle + 3.14159f / 2.0f),
					10.0f * sinf(-player.angle),
					10.0f * cosf(-player.angle),
					3.0f,
					(int)32, 0.0f
				}
			);
		}

		// Draw Ship
		DrawWireFrameModel(vecModelShip, player.x, player.y, player.angle, 2.0f);
		
		// Draw Score
		DrawString(olc::vi2d{ 2, 2 },std::string("Score: ") + std::to_string(nScore), olc::WHITE);

		return true;
	}

	void DrawWireFrameModel(const std::vector<std::pair<float, float>> &vecModelCoordinates, float x, float y, float r = 0.04, float s = 1.0f,  olc::Pixel col = olc::WHITE) {

		//pair.first = x coordinate
		//pair.second = y coordinate

		// Create translated model vector of coordinate pairs
		std::vector<std::pair<float, float>> vecTransformedCoordinates;
		int verts = vecModelCoordinates.size();
		vecTransformedCoordinates.resize(verts);


		// Rotate
		for (int i = 0; i < verts; i++) {
			vecTransformedCoordinates[i].first = vecModelCoordinates[i].first * cosf(r) - vecModelCoordinates[i].second * sinf(r);
			vecTransformedCoordinates[i].second = vecModelCoordinates[i].first * sinf(r) + vecModelCoordinates[i].second * cosf(r);
		}

		// Scale
		for (int i = 0; i < verts; i++) {
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first * s;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second * s;
		}

		// Translate
		for (int i = 0; i < verts; i++) {
			vecTransformedCoordinates[i].first = vecTransformedCoordinates[i].first + x;
			vecTransformedCoordinates[i].second = vecTransformedCoordinates[i].second + y;
		}

		// Draw Closed Polygon
		for (int i = 0; i < verts + 1; i++) {
			int j = (i + 1);

			DrawLine(vecTransformedCoordinates[i % verts].first, vecTransformedCoordinates[i % verts].second, vecTransformedCoordinates[j % verts].first, vecTransformedCoordinates[j % verts].second, col);
		}


	}

	void WrapCoordinates(float ix, float iy, float& ox, float& oy) {
		ox = ix;
		oy = iy;
		if (ix < 0.0f) ox = ix + (float)ScreenWidth();
		if (ix >= ScreenWidth()) ox = ix - (float)ScreenWidth();

		if (iy < 0.0f) oy = iy + (float)ScreenHeight();
		if (iy >= ScreenHeight()) oy = iy - (float)ScreenHeight();
	}
	bool Draw(int32_t x, int32_t y, olc::Pixel p)
	{
		float fx, fy;
		WrapCoordinates(x, y, fx, fy);
		olc::PixelGameEngine::Draw(fx, fy, p);

		return false;
	}
};


int main() {
	Asteroid Game;
	if (Game.Construct(300, 300, 2, 2))
		Game.Start();
}



// Rotate
//for (int i = 0; i < 3; i++) {
//	sx[i] = mx[i] * cosf(player.angle) - my[i] * sinf(player.angle);
//
//	sy[i] = mx[i] * sinf(player.angle) + my[i] * cosf(player.angle);
//}
//// Translate
//for (int i = 0; i < 3; i++) {
//	sx[i] = sx[i] + player.x;
//	sy[i] = sy[i] + player.y;
//}
//// Draw Closed Polygon
//for (int i = 0; i < 4; i++) {
//	int j = (i + 1);
//	DrawLine(sx[i % 3], sy[i % 3], sx[j % 3], sy[j % 3], olc::GREEN);
//}