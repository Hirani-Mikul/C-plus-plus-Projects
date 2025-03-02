#pragma once
#include "olcPixelGameEngine.h"
#include "Drawable.h"

class Entity {

public:
	Entity(std::vector<olc::vf2d> model, olc::vf2d pos = { 0.0f, 0.0f }, olc::Pixel col = olc::BLUE) : m_Model(model), m_Position(pos), m_Scale(1.0f), m_Color(col) {
	
		id = id_count;
		id_count++;
		std::cout << "Entity "<< id << " Created\n";
	}
	~Entity()
	{
		std::cout << "Entity " << id << " Destroyed\n";
	}

public:
	// Void methods
	void TranslateBy( const olc::vf2d translation_in ) {
		m_Position += translation_in;
	}
	
	// Setters
	void SetPos( const olc::vf2d pos_in ) {
		m_Position = pos_in;
	}
	void SetScale( const float scale_in ) {
		m_Scale = scale_in;
	}
	void SetID( const int id_in ) {
		id = id_in;
	}
	void SetColor( const olc::Pixel col ) {
		m_Color = col;
	}

	// Getters
	olc::vf2d GetPos () const {
		return m_Position;
	}
	float GetScale() const {
		return m_Scale;
	}
	int GetID() const {
		return id;
	}
	olc::Pixel GetColor() const {
		return m_Color;
	}

	std::vector<olc::vf2d> GetModel() const
	{
		return m_Model;
	}

	//virtual Drawable GetDrawable() const { 
	//	
	//	Drawable d(m_Model, m_Color);

	//	return d;
	//};

	virtual Drawable GetDrawable() const = 0;
	virtual float GetRadius() const { return 0; }
	virtual olc::vf2d GetSize() const { return olc::vf2d{ 0.0f, 0.0f }; };




	static int id_count;

protected:
	std::vector<olc::vf2d> m_Model;

	olc::vf2d m_Position;
	olc::Pixel m_Color;
	float m_Scale;

	int id = 0;

};

