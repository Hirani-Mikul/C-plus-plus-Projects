#pragma once

#include "olcPixelGameEngine.h"

enum class ActionMode : unsigned int {
	Panning = 0,
	Select,
	Circle,
	Rect,
	Zoom,
};

ActionMode CurrentMode = ActionMode::Panning;

class BarItem {
public:

	BarItem( olc::vf2d pos, int id ) : m_Position(pos), ID(id), m_Size(20.0f, 20.0f), m_Color(olc::WHITE){}

public:

	void Display( olc::PixelGameEngine* pge )
	{

		if (ID == (int)CurrentMode)
		{
			pge->DrawRect(m_Position, m_Size * 1.2f, olc::GREEN);
			pge->DrawPartialSprite(m_Position + olc::vf2d{ 2.0f, 2.0f }, m_Tile.get(), olc::vi2d{ 0, 0 }, m_Size);
		}
		else {
			pge->DrawRect(m_Position, m_Size, olc::WHITE);
			pge->DrawPartialSprite(m_Position, m_Tile.get(), olc::vi2d{ 0, 0 }, m_Size);
		}

	}

	void SelectStatus() {
	}

public:
	std::unique_ptr<olc::Sprite> m_Tile;

	bool m_IsSelected = false;

	olc::vf2d m_Position;
	olc::vf2d m_Size;
	olc::Pixel m_Color;

	int ID = 0;

};