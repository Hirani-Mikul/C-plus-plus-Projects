#include "CoordinateTransformer.h"
#include "CameraController.h"
#include "Polygon.h"
#include "MyMath.h"

float fWidth, fHeight;

class Game : public olc::PixelGameEngine
{
public:
	Game() {
		sAppName = "2D Shape Rotation";
	}

private:
	CoordinateTransformer ct = CoordinateTransformer(this);
	Camera cam = Camera(ct);
	CameraController camCtrl = CameraController(*this, cam);

	cCircle ball = cCircle({ 0.0f, 0.0f }, 20, 30.0f, olc::BLUE);

	Entity camCenter = Entity(Rectangle::Make(), { 0.0f, 0.0f }, fWidth, olc::RED);
	//Entity surface = Entity(Rectangle::Make(), { 0.0f, 0.0f }, );

public:

	bool OnUserCreate() override {

		fWidth = (float)ScreenWidth();
		fHeight = (float)ScreenHeight();

		return true;
	}

	void DrawCameraFrame() 
	{
		olc::vf2d camCenterPos = { cam.GetPos().x - camCenter.GetRadius() / 2.0f, cam.GetPos().y - camCenter.GetRadius() / 2.0f };
		camCenter.SetPos(camCenterPos);
		camCenter.SetRadius(fWidth * cam.GetScale());

		Drawable camCenterD = camCenter.GetDrawable();
		cam.DrawShape(camCenterD);
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::VERY_DARK_GREY);

		camCtrl.update();

		Drawable ballD = ball.GetDrawable();

		cam.DrawShape(ballD);

		DrawCameraFrame();

		return true;
	}

};


int main()
{
	Game app;
	if (app.Construct(600, 600, 1, 1))
		app.Start();

}