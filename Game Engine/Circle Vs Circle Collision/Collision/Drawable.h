#pragma once
#include "Shape.h"

class Drawable {

public:
	Drawable(const std::vector<olc::vf2d>& model, olc::Pixel col) : m_Model(&model), m_Col(col), m_ScaleX(1.0f), m_ScaleY(1.0f), m_Translation(0.0f, 0.0f) {};

public:

	// Void
	void Translate( const olc::vf2d &translation_in ) {
		m_Translation += translation_in;
	}

	void Scale( float scale_in ) {
		
		m_ScaleX *= scale_in;
		m_ScaleY *= scale_in;
		m_Translation *= scale_in;

	}
	void ScaleIndependent( float sx_in, float sy_in ) {
		
		m_ScaleX *= sx_in;
		m_ScaleY *= sy_in;
		m_Translation.x *= sx_in;
		m_Translation.y *= sy_in;
	}

	void Render( olc::PixelGameEngine *pge )
	{
		sShape::DrawPolygon( pge, *m_Model, m_Translation, m_ScaleX, m_ScaleY, m_Col );
	}

	// Setters

	// Getters


private:
	const std::vector<olc::vf2d>* m_Model;
	olc::Pixel m_Col;

	olc::vf2d m_Translation;

	float m_ScaleX;
	float m_ScaleY;

};