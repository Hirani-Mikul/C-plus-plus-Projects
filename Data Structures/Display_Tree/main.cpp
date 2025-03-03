#include "olcPixelGameEngine.h"

#include "Node.h"
#include "CameraController.h"

class App : public olc::PixelGameEngine
{
public:

	App()
	{
		sAppName = "TREE VISUALIZATION";
	}

public:

	bool OnUserCreate() override
	{

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::VERY_DARK_GREY);

		camCtrl.update();

		auto n1d = n1.getDrawable();

		cam.DrawShape(n1d);

		return true;
	}

private:

	CoordinateTransformer ct{ this };

	Camera cam{ ct };

	CameraController camCtrl{ *this, cam };

	Node n1 = Node({ .0f, .0f }, olc::BLUE, 1.0f, 15.0f, '2');
};


int main()
{
	App app;

	if (app.Construct(600, 600, 1, 1))
		app.Start();

	return 0;
}