#pragma once


#include "Drawable.h"

class CoordinateTransformer {
public:
	CoordinateTransformer() : pge{ nullptr }, m_width{ 0.0f }, m_height{ 0.0f } {}
	CoordinateTransformer(olc::PixelGameEngine* pge, float width = 600.0f, float height = 600.0f) : pge{ pge }, m_width{ width }, m_height{ height } {};

public:
	
	void drawEntity(Drawable& d) {
		const olc::vf2d offset = { m_width/2, m_height/2 };
		// Scale
		d.ScaleIndependent(1.0f, -1.0f);
		// Translate
		d.Translate(offset);
		// Render
		d.Render(pge);
	}

private:
	olc::PixelGameEngine* pge;
	float m_width;
	float m_height;
};