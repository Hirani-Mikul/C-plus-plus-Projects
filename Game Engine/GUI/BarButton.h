#pragma once
#include "olcPixelGameEngine.h"

class BarButton {

public:
	BarButton( olc::vf2d pos, int id ) : m_Position(pos), ID(id), m_Size(20.0f, 20.0f) {}

public:

	void Display( olc::PixelGameEngine* pge ) {

		//pge->DrawRect(m_Position, m_Size, olc::BLUE);
		pge->DrawPartialSprite(m_Position, m_Tile.get(), olc::vi2d{ 0, 0 }, m_Size);
	
	}

	void Action() {}

public:
	std::unique_ptr<olc::Sprite> m_Tile;

	olc::vf2d m_Position;
	olc::vf2d m_Size;

	int ID = 0;
};
