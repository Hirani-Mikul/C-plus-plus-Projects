#pragma once
#include "BarItemButtons.h"
#include "Utils.h"

class Toolbar {

public:
	Toolbar(olc::PixelGameEngine* pge) : pge(pge) {
	
		Construct();
	}

public:

	void Construct()
	{
		BarItem MoveIcon      = BarIcon({ 50.0f, 10.0f  }, { 20.0f, 20.0f });
		BarItem PointerIcon   = BarIcon({ 100.0f, 10.0f }, { 20.0f, 20.0f });
		BarIcon CircleIcon    = BarIcon({ 150.0f, 10.0f }, { 20.0f, 20.0f });
		BarIcon RectangleIcon = BarIcon({ 200.0f, 10.0f }, { 20.0f, 20.0f });

		MoveIcon.m_Tile       = std::make_unique<olc::Sprite>("./Sprites/move.png");
		PointerIcon.m_Tile    = std::make_unique<olc::Sprite>("./Sprites/pointer.png");
		CircleIcon.m_Tile     = std::make_unique<olc::Sprite>("./Sprites/circle.png");
		RectangleIcon.m_Tile  = std::make_unique<olc::Sprite>("./Sprites/rectangle.png");


		Slider RadiusSlider = Slider({ 300.0f, 10.0f }, { 100.0f, 20.0f }, olc::BLUE, 0, 100, 50, 10);

		BarItems.push_back(std::move(MoveIcon));
		BarItems.push_back(std::move(PointerIcon));
		BarItems.push_back(std::move(CircleIcon)); 
		BarItems.push_back(std::move(RectangleIcon));
		BarItems.push_back(std::move(RadiusSlider));

	}

	void Display() {

		pge->DrawRect(m_Position, olc::vf2d{ m_Width, m_Height }, olc::GREEN);

		pge->SetPixelMode(olc::Pixel::MASK);

		for (auto& i : BarItems)
		{
			i.Display(pge);
		}


		pge->SetPixelMode(olc::Pixel::NORMAL);

	}

	void Select( const olc::vf2d& cursor ) {
		
		for (auto& i : BarItems)
		{
			if (IsInside(cursor, i.GetPos(), i.GetSize()))
			{
				i.Select(cursor);
				switch (i.GetID())
				{
				case 0:
					CurrentMode = ActionMode::Panning;
					break;
				case 1:
					CurrentMode = ActionMode::Select;
					break;
				case 2:
					CurrentMode = ActionMode::Circle;
					break;
				case 3:
					CurrentMode = ActionMode::Rectangle;
					break;
				default:
					CurrentMode = ActionMode::Panning;
					break;
				}
				break;
			}
		}

	}

private:
	olc::PixelGameEngine* pge;

	olc::vf2d m_Position = { 25.0f, 0.0f };
	const float m_Width = 550.0f;
	const float m_Height = 40.0f;

	std::vector<olc::vf2d> m_Model = Shape::FillRect::Make();

	std::list<BarItem> BarItems;

};