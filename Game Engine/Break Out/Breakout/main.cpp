/*
https://github.com/OneLoneCoder/olcPixelGameEngine/wiki/TUTORIAL---Better-Collisions
*/

#include <iostream>
#include "olcPixelGameEngine.h"

class Breakout : public olc::PixelGameEngine {
public:
	Breakout() {
		sAppName = "Breakout Game";
	}

private:
	float fBatPos = 20.0f;
	float fBatWidth = 40.0f;
	float fBatSpeed = 250.0f;

	olc::vf2d vBallPos = { 0.0f, 0.0f };
	olc::vf2d vBallDir = { 0.0f, 0.0f };
	float fBallSpeed = 20.0f;
	float fBallRadius = 5.0f;

	olc::vi2d vBlockSize = { 16, 16 };
	std::unique_ptr<int[]> blocks;

	std::unique_ptr<olc::Sprite> sprTile;
	std::unique_ptr<olc::Sprite> sprFragment;
	std::unique_ptr<olc::Decal> decFragment;

	struct sFragment {
		olc::vf2d pos;
		olc::vf2d vel;
		float fAngle;
		float fTime;
		olc::Pixel color;
	};

	std::list<sFragment> listFragments;

	int gridX = 24;
	int gridY = 30;
public:

	void loadSprites() {

		// Load the sprite
		sprTile = std::make_unique<olc::Sprite>("./tut_tiles.png");

		// Load Fragment Sprite
		sprFragment = std::make_unique<olc::Sprite>("./tut_fragment.png");

		// Create decal of fragment
		decFragment = std::make_unique<olc::Decal>(sprFragment.get());
	}
	
	void createGrid() {
		blocks = std::make_unique<int[]>(gridX * gridY);

		for (int y = 0; y < gridY; y++) {
			for (int x = 0; x < gridX; x++) {

				if (x == 0 || y == 0 || x == gridX - 1)
					blocks[y * gridX + x] = 10;
				else
					blocks[y * gridX + x] = 0;

				if (x > 2 && x <= 20 && y > 3 && y <= 5)
					blocks[y * gridX + x] = 1;
				if (x > 2 && x <= 20 && y > 5 && y <= 7)
					blocks[y * gridX + x] = 2;
				if (x > 2 && x <= 20 && y > 7 && y <= 9)
					blocks[y * gridX + x] = 3;
			}
		}
	}

	void drawGrid() {
		SetPixelMode(olc::Pixel::MASK);

		for (int y = 0; y < gridY; y++) {
			for (int x = 0; x < gridX; x++) {
				switch (blocks[y * gridX + x])
				{
				case 0: break;
				case 10:
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(0, 0) * vBlockSize, vBlockSize);
					break;
				case 1:
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);
					break;
				case 2:
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(2, 0) * vBlockSize, vBlockSize);
					break;
				case 3:
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(3, 0) * vBlockSize, vBlockSize);
					break;
				default:
					break;
				}
			}
		}
		SetPixelMode(olc::Pixel::NORMAL);
	}

	void initializeBall() {

		// Start Ball

		float fAngle = float(rand()); float(RAND_MAX) * 2.0f * 3.14159f;

		fAngle = -0.4f;
		vBallDir = { cos(fAngle), sin(fAngle) };
		vBallPos = { 12.5f, 15.5f };
	}

	

	bool OnUserCreate() override {

		createGrid();

		loadSprites();

		initializeBall();

		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override {

		olc::vf2d vPotentialBallPos = vBallPos + vBallDir * fBallSpeed * fElapsedTime;

		olc::vf2d vTileBallRadialDims = { fBallRadius / vBlockSize.x, fBallRadius / vBlockSize.y };

		auto TestResolveCollisionPoint = [&](const olc::vf2d& point, olc::vf2d& hitpos, int& id) {

			olc::vi2d vTestPoint = vPotentialBallPos + vTileBallRadialDims * point;

			auto& tile = blocks[vTestPoint.y * gridX + vTestPoint.x];

			if (tile == 0) {
				return false;
			}
			else {
				bool bHitTile = tile < 10;
				if (bHitTile) {

					id = tile;
					hitpos = { float(vTestPoint.x), float(vTestPoint.y) };
					tile--;
				}

				if (point.x == 0.0f) vBallDir.y *= -1.0f;
				if (point.y == 0.0f) vBallDir.x *= -1.0f;

				return bHitTile;
			}
		};

		bool bHasHitTile = false;
		olc::vf2d hitpos;
		int hitid = 0;

		bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(0, -1), hitpos, hitid);
		bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(0, +1), hitpos, hitid);
		bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(-1, 0), hitpos, hitid);
		bHasHitTile |= TestResolveCollisionPoint(olc::vf2d(+1, 0), hitpos, hitid);


		if (bHasHitTile) {
			for (int i = 0; i < 50; i++) {
				sFragment f;
				f.pos = { hitpos.x + 0.5f, hitpos.y + 0.5f };
				float fAngle = float(rand()) / float(RAND_MAX) * 2.0f * 3.14159f;
				float fVelocity = float(rand()) / float(RAND_MAX) * 10.0f;
				f.vel = { fVelocity * cos(fAngle), fVelocity * sin(fAngle) };
				f.fAngle = fAngle;
				f.fTime = 3.0f;

				if (hitid == 1) f.color = olc::RED;
				if (hitid == 2) f.color = olc::GREEN;
				if (hitid == 3) f.color = olc::YELLOW;
				listFragments.push_back(f);

			}
		}

		// Fake Ground
		if (vBallPos.y > 20.0f) vBallDir.y *= -1.0f;

		vBallPos += vBallDir * fBallSpeed * fElapsedTime;

		// Update Fragments
		for (auto& f : listFragments) {
			f.vel += olc::vf2d(0.0f, 20.0f) * fElapsedTime;
			f.pos += f.vel * fElapsedTime;
			f.fAngle += 5.0f * fElapsedTime;
			f.fTime -= fElapsedTime;
			f.color.a = (f.fTime / 3.0f) * 255;
		}

		// Remove the dead fragments
		listFragments.erase(
			std::remove_if(listFragments.begin(), listFragments.end(), [](const sFragment& f) { return f.fTime < 0.0f; }), listFragments.end()
		);


		Clear(olc::DARK_BLUE);
		drawGrid();

		// Draw Ball
		FillCircle(vBallPos * vBlockSize, fBallRadius, olc::CYAN);

		// Draw Fragments
		for (auto& f : listFragments) {
			DrawRotatedDecal(f.pos * vBlockSize, decFragment.get(), f.fAngle, { 4, 4 }, {1, 1}, f.color);
		}

		return true;
	}
};

int main() {
	
	Breakout Game;

	if (Game.Construct(512, 480, 1, 1))
		Game.Start();

	//system("pause>0");
	return 0;
}