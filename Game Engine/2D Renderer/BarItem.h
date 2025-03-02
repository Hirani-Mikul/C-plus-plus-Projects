#pragma once
#include "olcPixelGameEngine.h"

enum class ActionMode : unsigned int {
	Panning = 0,
	Select,
	Circle,
	Rectangle,
};
ActionMode CurrentMode = ActionMode::Panning;

class BarItem {
public:
	BarItem( olc::vf2d pos, olc::vf2d size, olc::Pixel col = olc::GREEN ) : m_Position(pos), m_Size(size), m_Color(col), m_IsSelected(false), m_Tile(nullptr)
	{
		ID = ID_COUNTER;
		ID_COUNTER++;


		m_SpriteSelectedPosition = m_Position + (m_Size * 1.1f - m_Size);
		std::cout << "Item created\n";
	}

public:

	virtual void Display(olc::PixelGameEngine* pge) {

		if (ID == (int)CurrentMode)
		{
			pge->DrawRect(m_Position , m_Size * 1.2f, olc::GREEN);
			pge->DrawPartialSprite(m_SpriteSelectedPosition, m_Tile.get(), olc::vi2d{ 0, 0 }, m_Size);
		}
		else {
			pge->DrawRect(m_Position, m_Size, m_Color);
			pge->DrawPartialSprite(m_Position, m_Tile.get(), olc::vi2d{ 0, 0 }, m_Size);
		}
	}

	virtual void Action() {
		std::cout << "Action Executed\n";
	}

	virtual void Select(const olc::vf2d& cursor) { std::cout << "Selecting\n"; }

	int GetID() const { return ID;  }

	olc::vf2d GetPos() const { return m_Position; }
	olc::vf2d GetSize() const { return m_Size; }


public:
	static int ID_COUNTER;
	std::unique_ptr<olc::Sprite> m_Tile;

protected:
	int ID;


	olc::vf2d m_Position;
	olc::vf2d m_Size;
	olc::Pixel m_Color;

	olc::vf2d m_SpriteSelectedPosition;

	bool m_IsSelected;

};
int BarItem::ID_COUNTER = 0;
