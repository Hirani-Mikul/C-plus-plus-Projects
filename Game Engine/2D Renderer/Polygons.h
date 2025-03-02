#pragma once
#include "Entity.h"

class Circle : public Entity {

public:
	Circle( std::vector<olc::vf2d> model, olc::vf2d pos, olc::Pixel col, float radius = 10.0f ) : Entity(model, pos, col), m_Radius(radius) {}

	//Circle( const Circle& c ) : Entity(c.GetModel(), c.GetPos(), c.GetColor()), m_Radius( c.GetRadius() )
	//{
	//	std::cout << "Circle " << id << " Copied\n";
	//}

public:
	Drawable GetDrawable() const {

		Drawable d(m_Model, m_Color);
		d.Scale(m_Radius);
		d.Scale(m_Scale);
		d.Translate(m_Position);

		return d;

	}
	float GetRadius() const {

		return m_Radius;
	}

	bool isOverlapping(  ) {

	}

private:
	float m_Radius;

};

class Rect : public Entity {

public:
	Rect(std::vector<olc::vf2d> model, olc::vf2d pos, olc::Pixel col, float length = 10.0f, float height = 10.0f) : Entity(model, pos, col), m_Length(length), m_Height(height) {}

public:
	Drawable GetDrawable() const {

		Drawable d(m_Model, m_Color);
		d.ScaleIndependent(m_Length, m_Height);
		d.Scale(m_Scale);
		d.Translate(m_Position);

		return d;

	}

	olc::vf2d GetSize() const {

		return olc::vf2d{ m_Length, m_Height };
	}

private:
	float m_Length, m_Height;

};
