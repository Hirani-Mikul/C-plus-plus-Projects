#pragma once
#include "Create.h"
#include "MyMath.h"

class Drawable {

public:
	Drawable(const std::vector<olc::vf2d> &model, olc::Pixel col) : m_Model(&model), m_Color(col), m_Translation(0.0f, 0.0f), m_ScaleX(1.0f), m_ScaleY(1.0f), m_Angle(0.0f) {}
public:
	// Void Methods
	void Translate( const olc::vf2d &translation_in ) {
		
		m_Translation += translation_in;

	}
	void Scale( float scale_in ) {
		
		m_ScaleX *= scale_in;
		m_ScaleY *= scale_in;
		m_Translation *= scale_in;

	}
	//void Rotate( const float angle_in )
	//{
	//	m_Angle += angle_in;
	//}
	void Rotate(float angle_in)
	{
		m_Angle += angle_in;

		m_Translation = GetRotated(m_Translation, angle_in);
		
	}
	void ScaleIndependent( float sx_in, float sy_in ) {
		
		m_ScaleX *= sx_in;
		m_ScaleY *= sy_in;
		m_Translation.x *= sx_in;
		m_Translation.y *= sy_in;

	}

	void Render( olc::PixelGameEngine* pge ) {
		Create::DrawPolygon(pge, *m_Model, m_Translation, m_ScaleX, m_ScaleY, m_Angle,  m_Color);
	}

	// Setters

	// Getters

private:
	const std::vector<olc::vf2d>* m_Model;
	
	olc::vf2d m_Translation;
	olc::Pixel m_Color;

	float m_ScaleX;
	float m_ScaleY;
	float m_Angle;


};