#include "Objects.h"

int WIDTH;
int HEIGHT;

void createBoundry(olc::PixelGameEngine*);

class Example : public olc::PixelGameEngine {

private:
	olc::vi2d vBlockSize = { 16, 16 };
	std::unique_ptr<int[]> blocks;
	std::unique_ptr<olc::Sprite> sprTile;

	void createGrid() {
		blocks = std::make_unique<int[]>(38 * 30);

		for (int y = 0; y < 30; y++) {
			for (int x = 0; x < 38; x++) {
				if (x == 0 || y == 0 || x == 37)
					blocks[y * 38 + x] = 10;
				else 
					blocks[y * 38 + x] = 0;

				if (x > 2 && x <= 34 && y > 3 && y <= 5)
					blocks[y * 38 + x] = 1;
				if (x > 2 && x <= 34 && y > 5 && y <= 7)
					blocks[y * 38 + x] = 2;
				if (x > 2 && x <= 34 && y > 7 && y <= 9)
					blocks[y * 38 + x] = 3;
			}
		}

		//sprTile = std::make_unique<olc::Sprite>("./tut_tile.png");
		sprTile = std::make_unique<olc::Sprite>("./tut_tiles.png");
	}
	void drawGrid() {
		SetPixelMode(olc::Pixel::MASK);
		for (int y = 0; y < 30; y++) {
			for (int x = 0; x < 38; x++) {
				switch (blocks[y * 38 + x])
				{
				case 0: break;
				case 10: // Boundry
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(0, 0) * vBlockSize, vBlockSize);
					break;
				case 1: // Red
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);
					break;
				case 2: // Green
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(2, 0) * vBlockSize, vBlockSize);
					break;
				case 3: // Yellow
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(3, 0) * vBlockSize, vBlockSize);
					break;
				default:
					break;
				}
			}
		}
		SetPixelMode(olc::Pixel::NORMAL);

	}

public:

	Example() {
		sAppName = "Trial - First Project";
	}

	Paddle paddle;
	Ball ball;

	bool OnUserCreate() override {

		WIDTH = ScreenWidth();
		HEIGHT = ScreenHeight();
		createGrid();

		paddle = Paddle(200.0f, 580.0f, WIDTH, HEIGHT);
		ball = Ball(200.0f, 200.0f, 8.0f);
		return true;
	}

	void displayAndUpdateObjects(float fElapsedTime) {
		// DRAW PADDLE
		paddle.display(this);
		movePaddle(fElapsedTime);
		// DRAW BALL
		ball.display(this);
		ball.update(paddle.pos, paddle.pWidth, paddle.pHeight, fElapsedTime);
		ball.checkEdges();
		dragBall();
		zoomBall();
	}

	void movePaddle(float fElapsedTime) {
		if (GetKey(olc::Key::LEFT).bHeld) paddle.update(-1, fElapsedTime);
		if (GetKey(olc::Key::RIGHT).bHeld) paddle.update(1, fElapsedTime);
	}

	void dragBall() {
		if (GetMouse(0).bHeld) {
			ball.dragMe(float(GetMouseX()), float(GetMouseY()));
		}
	}

	void zoomBall() {
			if (GetKey(olc::Key::CTRL).bHeld && GetMouseWheel() > 0) ball.Zoom(3.0f);
			if (GetKey(olc::Key::CTRL).bHeld && GetMouseWheel() < 0) ball.Zoom(-3.0f);
	}

	bool OnUserUpdate(float fElapsedTime) override {

		

		// Clear the screen before the next update
		Clear(olc::DARK_BLUE);
		drawGrid();
		// DRAW BOUNDRY
		//createBoundry(this);

		//displayAndUpdateObjects(fElapsedTime);
		return true;
	}
};

void createBoundry(olc::PixelGameEngine* pge) {

	pge->DrawLine(10, 10, pge->ScreenWidth() - 10, 10, olc::YELLOW);
	pge->DrawLine(10, 10, 10, pge->ScreenHeight() - 10, olc::YELLOW);
	pge->DrawLine(pge->ScreenWidth() - 10, 10, pge->ScreenWidth() - 10,pge->ScreenHeight() - 10, olc::YELLOW);
}

int main() {

	Example demo;

	if (demo.Construct(608, 608, 1, 1, false, true)) {
		demo.Start();
	}

	//return 0;
	//system("pause>0");
}


// CODE FOR FIXED FRAME STEP :: 60 FPS


//private:
//	float fTargetFrameTime = 1.0f / 100.0f; // Virtual FPS of 100fps
//	float fAccumulatedTime = 0.0f;


//fAccumulatedTime += fElapsedTime;
//
//if (fAccumulatedTime >= fTargetFrameTime)
//{
//	fAccumulatedTime -= fTargetFrameTime;
//	fElapsedTime = fTargetFrameTime;
//}
//else return true; // Don't do anything this frame