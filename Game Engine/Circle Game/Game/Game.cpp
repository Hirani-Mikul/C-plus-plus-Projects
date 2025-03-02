//#include "CameraControls.h"
//#include "Ball.h"
//
//float fWidth, fHeight;
//
//class Game : public olc::PixelGameEngine
//{
//public:
//	Game() {
//		sAppName = "Ball Collision Game";
//	}
//public:
//
//	void AddBall(float x, float y, float r)
//	{
//		int randIndex = rand() % 4;
//
//		Ball b = Ball({x, y}, r, colors[randIndex]);
//
//		b.SetId(balls.size());
//		balls.emplace_back(b);
//	}
//
//	bool OnUserCreate() override {
//
//		fWidth = (float)ScreenWidth();
//		fHeight = (float)ScreenHeight();
//
//		for (int i = 0; i < 10; i++)
//		{
//			const float x = (float)(rand() % 1200 - 600);
//			const float y = (float)(rand() % 1200 - 600);
//			const float r = (float)(rand() % 100 + 50);
//			AddBall(x, y, r);
//		}
//		
//		return true;
//	}
//
//	void DrawAndUpdateBall(float fElapsedTime) {
//		
//		// Ball is selected if cursor position is within the circle boundry (Right click)
//		if (GetMouse(1).bPressed) {
//			bSelectedBall = nullptr;
//
//			for (auto& b : balls)
//			{
//				if (b.isSelected(vCursor))
//				{
//					bSelectedBall = &b;
//					break;
//				}
//			}
//		}
//		if (GetMouse(1).bHeld) {
//			if (bSelectedBall)
//			{
//				bSelectedBall->SetPos( vCursor );
//			}
//		}
//		if (GetMouse(1).bReleased) {
//			
//			bSelectedBall = nullptr;
//		}
//
//		// Handle Static Collision
//		for (auto& b : balls)
//		{
//			for (auto& target : balls)
//			{
//				if (b.GetId() != target.GetId())
//				{
//					b.CheckCollision(target);
//				}
//			}
//
//			b.Update(fElapsedTime);
//			Drawable bd = b.GetDrawable();
//			cam.DrawShape(bd);
//		}
//	}
//
//	bool OnUserUpdate(float fElapsedTime) override {
//
//		const olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };
//
//		cam.TransformCursorCoordinates( vMouse, vCursor );
//
//		camCtrl.Update();
//
//		Clear(olc::VERY_DARK_GREY);
//
//		DrawAndUpdateBall(fElapsedTime);
//
//		return true;
//	}
//
//private:
//	CoordinateTransformer ct = CoordinateTransformer(this);
//
//	Camera cam = Camera(ct);
//	CameraController camCtrl = CameraController(*this, cam);
//
//	olc::vf2d vCursor = { 0.0f, 0.0f };
//
//	std::vector<Ball> balls;
//	Ball* bSelectedBall = nullptr;
//
//
//	olc::Pixel colors[5] = { olc::GREEN, olc::BLUE, olc::YELLOW, olc::DARK_CYAN, olc::DARK_MAGENTA };
//
//};
//
//int main()
//{
//	Game app;
//	if (app.Construct(600, 600, 1, 1))
//		app.Start();
//}
