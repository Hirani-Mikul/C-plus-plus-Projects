#pragma once
#include "BarItem.h"
#include "BarButton.h"
#include "Slider.h"

class Toolbar {

public:
	Toolbar(olc::PixelGameEngine* pge) : pge(pge) {}

public:
	void Construct()
	{
		Items.reserve(5);
		for (int i = 0; i < 5; i++)
		{
			const olc::vf2d pos = { i * 60.0f + 40.0f, 20.0f };

			Items.emplace_back( pos, i );
		}
		Items[0].m_Tile = std::make_unique<olc::Sprite>("./Sprites/move.png");
		Items[1].m_Tile = std::make_unique<olc::Sprite>("./Sprites/pointer.png");
		Items[2].m_Tile = std::make_unique<olc::Sprite>("./Sprites/circle.png");
		Items[3].m_Tile = std::make_unique<olc::Sprite>("./Sprites/rectangle.png");

		Buttons.push_back(BarButton({ 460.0f, 20.0f }, 0));
		Buttons.push_back(BarButton({ 500.0f, 20.0f }, 1));

		Buttons[0].m_Tile = std::make_unique<olc::Sprite>("./Sprites/plus.png");
		Buttons[1].m_Tile = std::make_unique<olc::Sprite>("./Sprites/minus.png");

		//slider.Construct();

	}
	void Display()
	{
		pge->DrawRect(m_Position, m_Size, olc::GREEN);

		pge->SetPixelMode(olc::Pixel::MASK);
		for (auto& i : Items)
			i.Display(pge);

		for (auto& b : Buttons)
			b.Display(pge);

		pge->SetPixelMode(olc::Pixel::NORMAL);

		slider.Display(pge);
		slider2.Display(pge);

	}

	void SelectItem( const olc::vf2d& cursor )
	{
		for (auto& i : Items)
		{
			auto isInside = [&]( const olc::vf2d pos, const olc::vf2d size ) {
			
				return ( cursor.x >= pos.x && cursor.x <= pos.x + size.x && cursor.y >= pos.y && cursor.y <= pos.y + size.y );

			};

			if (isInside(i.m_Position, i.m_Size))
			{
				switch (i.ID)
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
					CurrentMode = ActionMode::Rect;
					break;
				case 4:
					CurrentMode = ActionMode::Zoom;
					break;
				default:
					CurrentMode = ActionMode::Panning;
					break;
				}
				//UpdateSelection();
				break;
			}

		}

		slider.Select(cursor);
		slider2.Select( cursor );
	}

	void ButtonAction( const olc::vf2d& cursor, float &shapesize )
	{
		for (auto& b : Buttons)
		{
			auto isInside = [&](const olc::vf2d pos, const olc::vf2d size) {

				return (cursor.x >= pos.x && cursor.x <= pos.x + size.x && cursor.y >= pos.y && cursor.y <= pos.y + size.y);

			};

			if (isInside(b.m_Position, b.m_Size))
			{
				switch (b.ID)
				{
				case 0:
					std::cout << "Add\n";
					shapesize += 10.0f;
					break;
				case 1:
					std::cout << "Subtract\n";
					shapesize -= 10.0f;
					break;
				default:
					break;
				}
			}
		}
	}

	void UpdateSelection() {
		for (auto& i : Items)
		{
			if (i.ID == (int)CurrentMode)
				i.m_IsSelected = true;
			else i.m_IsSelected = false;
		}
	}

	void Slide( float dir ) {
		slider.Slide(dir);
		slider2.Slide(dir);
	}

	float GetSliderValue() const {

		return slider.GetValue();

	}
	float GetSliderValue2() const {

		return slider2.GetValue();

	}

public:
	//ActionMode CurrentMode = ActionMode::Panning;

private:
	olc::PixelGameEngine* pge;

	const olc::vf2d m_Position = { 25.0f, 10.0f };
	const olc::vf2d m_Size = { 550.0f, 40.0f };

	std::vector<BarItem> Items;
	std::vector<BarButton> Buttons;

	Slider slider = Slider({ 300.0f, 80.0f }, { 200.0f, 20.0f }, olc::BLUE, 10.0f, 100.0f, 1.0f, 50.0f);
	Slider slider2 = Slider({ 300.0f, 130.0f }, { 400.0f, 20.0f }, olc::BLUE, -100.0f, 680.0f, 2.0f, 500.0f);

};