#pragma once

#include "Renderer.h"

class Drawable {

public:
	Drawable(const std::vector<olc::vf2d>& model, olc::Pixel color) : m_Model{ &model }, m_Color{ color }, m_Translation{ 0.0f, 0.0f }, m_scale_x{ 1.0f }, m_scale_y{ 1.0f } {}
	//Drawable(const std::vector<olc::vf2d>& model, olc::Pixel color) : m_Model{ &model }, m_Color{ color }, m_Translation{ 0.0f, 0.0f }, m_scale_x{ 1.0f }, m_scale_y{ 1.0f } {}


public:
	void Translate(const olc::vf2d& translation_in) {
		m_Translation += translation_in;
	}
	void Scale(float scale_in) { 

		m_scale_x *= scale_in;
		m_scale_y *= scale_in;
		m_Translation *= scale_in;
	}

	void rotate(float angle_in) { m_angle += angle_in; }

	void ScaleIndependent(float sx_in, float sy_in) {
		
		m_scale_x *= sx_in;
		m_scale_y *= sy_in;
		m_Translation.x *= sx_in;
		m_Translation.y *= sy_in;
	}

	void Render( olc::PixelGameEngine* pge ) {

		Renderer::Draw(pge, *m_Model, m_Translation, m_scale_x, m_scale_y, m_angle, m_Color);
	}

private:
	
	const std::vector<olc::vf2d>* m_Model;
	olc::vf2d m_Translation;
	olc::Pixel m_Color;
	
	float m_scale_x;
	float m_scale_y;
	float m_angle;
};