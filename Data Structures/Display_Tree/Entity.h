#pragma once
#include "olcPixelGameEngine.h"
#include "Drawable.h"

class Entity
{
public:

	Entity(olc::vf2d pos = { 0.0f, 0.0f }, olc::Pixel col = olc::BLUE, float scale = 1.0f, float radius = 15.0f) : m_Position{ pos }, m_Color{ col }, m_Scale{ scale }, m_Radius{ radius } {}

public:

	void TranslateBy(const olc::vf2d& translation_in)
	{
		m_Position += translation_in;
	}

	void setPos(const olc::vf2d& pos_in) 
	{
		m_Position = pos_in;
	}
	void setScale(float scale_in)
	{
		m_Scale = scale_in;
	}

	olc::vf2d getPos() const { return m_Position; }
	float getScale() const { return m_Scale; }

	Drawable getDrawable() const
	{
		Drawable d{ m_Color };
		d.Scale(m_Radius);
		d.Scale(m_Scale);
		d.Translate(m_Position);

		return d;

	}

private:
	olc::vf2d m_Position;
	olc::Pixel m_Color;

	float m_Scale;

	float m_Radius;
};