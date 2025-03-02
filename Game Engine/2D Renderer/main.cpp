#include "Shape.h"
#include "Polygons.h"
#include "Map.h"
#include"CameraController.h"
#include "Toolbar.h"


float fWidth, fHeight;
int Entity::id_count = 0;

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "2D Renderer";
	}

public:

	bool OnUserCreate() override {

		fWidth = (float)ScreenWidth();
		fHeight = (float)ScreenHeight();

		map.Construct();

		map.AppendChild(c1);
		map.AppendChild(c2);
		map.AppendChild(c3);


		return true;
	}

	void AddEntity( olc::vf2d pos, int verts, float radius )
	{
		if (colorCounter >= 6) colorCounter = 0;
		olc::vf2d WorldCoordinate = { 0.0f, 0.0f };
		cam.ScreenToWorld(pos, WorldCoordinate);
		if (CurrentMode == ActionMode::Circle)
			entityList.emplace_back(Circle(Shape::Ellipse::Make(verts), WorldCoordinate, colors[colorCounter], radius));
		else return;
		//else if (CurrentMode == ActionMode::Rectangle)
		//	entityList.emplace_back(Rect(Shape::Rect::Make(), WorldCoordinate, colors[colorCounter], radius, radius));
		//else entityList.emplace_back(Circle(Shape::Ellipse::Make(verts), WorldCoordinate, colors[colorCounter], radius));

		map.AppendChild(entityList.back());
		colorCounter++;
	}

	void SelectEntity(olc::vf2d pos)
	{
		olc::vf2d WorldCoordinate = { 0.0f, 0.0f };
		cam.ScreenToWorld(pos, WorldCoordinate);

		map.SelectEntity(WorldCoordinate);

	}

	void MoveSelectedEntity( float fElapsedTime ) {
		
		if (GetKey(olc::Key::A).bHeld)
			map.MoveSelectedEntity({ -1.0f * fElapsedTime, 0.0f });
		if (GetKey(olc::Key::W).bHeld)
			map.MoveSelectedEntity({ 0.0f, 1.0f * fElapsedTime });
		if (GetKey(olc::Key::D).bHeld)
			map.MoveSelectedEntity({ 1.0f * fElapsedTime, 0.0f });
		if (GetKey(olc::Key::S).bHeld)
			map.MoveSelectedEntity({ 0.0f, -1.0f * fElapsedTime });
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		const olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		Clear(olc::VERY_DARK_GREY);

		toolbar.Display();

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			if (CurrentMode == ActionMode::Select)
				SelectEntity(vMouse);

			else
			{
				int verts = rand() % 20 + 10;
				float radius = (float)(rand() % 160 + 80);
				AddEntity(vMouse, verts, radius);
			}
		}

		if (GetMouse(0).bPressed)
		{
			toolbar.Select(vMouse);
		}

		if (CurrentMode != ActionMode::Select)
		{
			CameraControls.update();
		}

		MoveSelectedEntity(fElapsedTime);
		map.Draw();

		if (GetKey(olc::Key::DEL).bPressed)
		{
			map.DeleteChild();
		}

		return true;
	}

private:

	Toolbar toolbar = Toolbar(this);

	CoordinateTransformer ct = CoordinateTransformer(this);
	Camera cam = Camera(ct);
	CameraController CameraControls = CameraController(*this, cam);
	Map map = Map(cam);

	Circle c1 = Circle(Shape::Ellipse::Make(20), { 0.0f, 0.0f }, olc::RED, 60.0f);
	Circle c2 = Circle(Shape::Ellipse::Make(10), { 100.0f, 0.0f }, olc::GREEN, 40.0f);
	Circle c3 = Circle(Shape::Ellipse::Make(15), {0.0f, -100.0f}, olc::YELLOW, 800.0f);

	std::list<Circle> entityList;

	std::vector<olc::Pixel> colors = { olc::RED, olc::GREEN, olc::BLUE, olc::YELLOW, olc::WHITE, olc::VERY_DARK_RED };

	int colorCounter = 0;
};

int main()
{
	Game app;
	if (app.Construct(600, 600, 1, 1))
		app.Start();
}