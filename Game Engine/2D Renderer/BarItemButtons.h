#pragma once

#include "BarItem.h"

class BarIcon : public BarItem
{
public:
	BarIcon( olc::vf2d pos, olc::vf2d size, olc::Pixel col = olc::WHITE ) : BarItem(pos, size, col) {}

public:

	void Select(const olc::vf2d& cursor) override
	{
		auto tmode = ActionMode::Circle;
		//auto tmode = (ActionMode)2;

		switch (tmode)
		{
		case ActionMode::Panning:
			std::cout << "Panning\n";
			break;
		case ActionMode::Select:
			std::cout << "Select\n";
			break;
		case ActionMode::Circle:
			std::cout << "Circle\n";
			break;
		case ActionMode::Rectangle:
			std::cout << "Rectangle\n";
			break;
		default:
			std::cout << "Nothing\n";
			break;
		}
	}

private:

};

class Slider : public BarItem 
{
public:
	Slider(olc::vf2d pos, olc::vf2d size, olc::Pixel col, float min, float max, float value, float step) : BarItem(pos, size, col), m_Min(min), m_Max(max), m_CurrentValue(value), m_Step(step) {
		
		Construct();
	}
public:
	void Construct() {
		
		m_ValuePosition = m_Position;
		m_Tile = nullptr;

	}

	void Select(const olc::vf2d& cursor ) {
		
	}

	void Display( olc::PixelGameEngine* pge ) override {
		
		pge->FillRect(m_Position - m_Size / 2.0f, m_Size, olc::WHITE);

		if (!m_IsSelected)
		{
			std::cout << "Drawing\n";
			pge->FillCircle(m_ValuePosition, m_Size.y, m_Color);
		}
		else
			pge->FillCircle(m_ValuePosition, m_Size.y, olc::GREEN);
	}
	
	void Slide() {}

	float GetValue() const { return m_CurrentValue; }

private:
	olc::vf2d m_ValuePosition;
	
	float m_Min;
	float m_Max;
	float m_Step;

	float m_CurrentValue;
};