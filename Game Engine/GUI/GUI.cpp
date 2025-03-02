#include "Toolbar.h"

class GUI : public olc::PixelGameEngine
{
public:
	GUI()
	{
		sAppName = "GUI INTERFACE";
	}

public:

	bool OnUserCreate() override {

		toolbar.Construct();

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		const olc::vf2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };

		Clear(olc::VERY_DARK_GREY);

		if (GetMouse(0).bPressed)
		{
			m_Lastpos = vMouse;
			toolbar.SelectItem(vMouse);
			toolbar.ButtonAction(vMouse, m_ShapeSize);
		}

		if (GetKey(olc::Key::LEFT).bHeld)
		{
			toolbar.Slide(-1.0f * fElapsedTime);
		}
		if (GetKey(olc::Key::RIGHT).bHeld)
		{
			toolbar.Slide(1.0f * fElapsedTime);
		}

		if (GetMouse(0).bHeld)
		{
			auto delta = vMouse - m_Lastpos;

			m_Value += delta.x;
			toolbar.Slide( delta.x * fElapsedTime );

			m_Lastpos = vMouse;
		}

		toolbar.Display();

		std::string CurrentModeTxt = "Panning";

		switch (CurrentMode)
		{
		case ActionMode::Panning:
			CurrentModeTxt = "Panning";
			break;
		case ActionMode::Select:
			CurrentModeTxt = "Select";
			break;
		case ActionMode::Circle:
			CurrentModeTxt = "Circle";
			break;
		case ActionMode::Rect:
			CurrentModeTxt = "Rect";
			break;
		case ActionMode::Zoom:
			CurrentModeTxt = "Zoom";
			break;
		default:
			CurrentModeTxt = "Panning";
			break;
		}

		DrawString(olc::vi2d{ 250, 200 }, std::to_string(std::round(toolbar.GetSliderValue())), olc::GREEN, 2);
		DrawString(olc::vi2d{ 250, 250 }, std::to_string( std::round(toolbar.GetSliderValue2())), olc::GREEN, 2);
		DrawString(olc::vi2d{ 250, 300 }, std::to_string(m_ShapeSize), olc::GREEN, 2 );
		DrawString(olc::vi2d{ 250, 350 }, CurrentModeTxt, olc::BLUE, 2);

		DrawString(olc::vi2d{ 250, 400 }, std::to_string(std::round(m_Value)), olc::GREEN, 2);

		return true;
	}

private:
	
	Toolbar toolbar = Toolbar(this);

	float m_ShapeSize = 10.0f;

	float m_Value = 0.0f;

	olc::vf2d m_Lastpos = { 0.0f, 0.0f };
};

int main()
{
	GUI app;
	if (app.Construct(600, 600, 1, 1))
		app.Start();
}