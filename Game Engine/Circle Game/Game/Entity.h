#pragma once
#include "olcPixelGameEngine.h"
#include "MyMath.h"

class Entity {
public:
	Entity(std::vector<olc::vf2d> model, olc::vf2d pos, float radius, olc::Pixel col ) : m_Model(std::move(model)), m_Position(pos), m_Radius(radius), m_Scale(1.0f), m_Color(col), m_Angle(0.0f)
	{
	}

public:
	// Void methods

	void Translate(const olc::vf2d& offset) {

		m_Position += offset;

	}

	// Setters
	void SetPos( const olc::vf2d &pos) {
		m_Position = pos;
	}
	void SetRadius( const float radius ) {
		m_Radius = radius;
	}
	void SetScale( const float scale_in ) {
		m_Scale = scale_in;
	}
	void SetAngle( const float angle_in )
	{
		m_Angle = angle_in;
	}

	// Getters

	const olc::vf2d GetPos() const {
		return m_Position;
	}

	const float GetRadius() const {

		return m_Radius;
	}
	const float GetScale() const {

		return m_Scale;
	}

	olc::Pixel GetColor() const
	{
		return m_Color;
	}
	float GetAngle() const
	{
		return m_Angle;
	}

	
	Drawable GetDrawable() const {
		Drawable d(m_Model, m_Color);
		d.Scale(m_Radius);
		d.Scale(m_Scale);
		d.Rotate(m_Angle);
		d.Translate(m_Position);

		return d;

	}

public:
	float m_RotationDir = 1.0f;

protected:
	std::vector<olc::vf2d> m_Model;

	olc::vf2d m_Position;
	olc::Pixel m_Color;

	float m_Radius;
	float m_Scale;
	float m_Angle;

};