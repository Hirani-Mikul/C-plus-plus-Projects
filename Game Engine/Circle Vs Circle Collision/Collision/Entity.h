#pragma once
#include "olcPixelGameEngine.h"
#include "Drawable.h"

class Entity {

public:
	Entity() {};

	Entity( std::vector<olc::vf2d> model, olc::vf2d position, float radius = 10.0f, olc::Pixel col = olc::BLUE ) : m_Model(std::move(model)), m_Position(position), m_Radius(radius), m_Col(col), m_Scale(1.0f) {};

public:

	// Void Functions
	void TranslateBy(olc::vf2d offset_in) {
		m_Position += offset_in;
	};

	 //Getter Methods
	//std::vector<olc::vf2d> GetModel() const {
	//	
	//	auto poly = m_Model;

	//	for (auto& v : poly)
	//	{
	//		v *= m_Radius;
	//		v += m_Position;
	//	}

	//	return poly;

	//}

	virtual Drawable GetDrawable() const {

		Drawable d(m_Model, m_Col);
		d.Scale(m_Radius);
		d.Scale(m_Scale);
		d.Translate(m_Position);

		return d;

	}


	olc::vf2d GetPos() const {
		return m_Position;
	}

	float GetScale() const {

		return m_Scale;
	}

	// Setter Methods

	void SetScale(const float scale_in)
	{
		m_Scale = scale_in;
	}

	void SetPos(const olc::vf2d position_in) {
		m_Position = position_in;
	}

protected:
	std::vector<olc::vf2d> m_Model;

	olc::vf2d m_Position;
	float m_Radius;
	float m_Scale;
	olc::Pixel m_Col;
};