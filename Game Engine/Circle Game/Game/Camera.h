#pragma once
#include "CoordinateTransformer.h"
#include "Drawable.h"


class Camera {

public:
	Camera( CoordinateTransformer &ct ) : ct(ct), m_Position(0.0f, 0.0f), m_Scale(1.0f), m_Angle(0.0f) {};

public:
	// Void methods
	void MoveTo( olc::vf2d position_in ) {
		m_Position = position_in;
	}
	void MoveBy( const olc::vf2d &translation_in ) {
		m_Position += translation_in;
	}

	void DrawShape( Drawable &drawable ) const {

		drawable.Translate(-m_Position);
		drawable.Scale(m_Scale);
		drawable.Rotate(m_Angle);

		ct.DrawShape(drawable);
	}
	
	// Setters
	void SetScale(float scale_in)
	{
		m_Scale = scale_in;
	}
	void SetAngle(const float angle_in)
	{
		m_Angle = angle_in;	
	}

	// Getters
	const float GetScale() const {

		return m_Scale;
	}
	olc::vf2d GetPos() const {

		return m_Position;
	}
	float GetAngle() const
	{
		return m_Angle;
	}

	void TransformCursorCoordinates( olc::vf2d screenCoord, olc::vf2d &worldCoord ) {

		
		CoordinateTransformer::ScreenToWorld( screenCoord, worldCoord );
		worldCoord = worldCoord / m_Scale + m_Position;
	}

private:
	CoordinateTransformer& ct;

	olc::vf2d m_Position;
	float m_Scale;
	float m_Angle;

};